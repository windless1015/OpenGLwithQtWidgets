#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QMatrix4x4>

//摄像机（观察矩阵）
//QOpenGLWidget窗口上下文
//QOpenGLFunctions访问OpenGL接口，可以不继承作为成员变量使用
class GLCamera
        : public QOpenGLWidget
        , protected QOpenGLFunctions_3_3_Core
{
public:
    explicit GLCamera(QWidget *parent = nullptr);
    ~GLCamera();

protected:
    //【】继承QOpenGLWidget后重写这三个虚函数
    //设置OpenGL资源和状态。在第一次调用resizeGL或paintGL之前被调用一次
    void initializeGL() override;
    //渲染OpenGL场景，每当需要更新小部件时使用
    void paintGL() override;
    //设置OpenGL视口、投影等，每当尺寸大小改变时调用
    void resizeGL(int width, int height) override;

    //按键操作,重载Qt的事件处理
    void keyPressEvent(QKeyEvent *event) override;
    //鼠标操作,重载Qt的事件处理
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void calculateCamera();
    QMatrix4x4 getViewMatrix();

private:
    //着色器程序
    QOpenGLShaderProgram shaderProgram;
    //顶点数组对象
    QOpenGLVertexArrayObject vao;
    //顶点缓冲
    QOpenGLBuffer vbo;
    //纹理（因为不能赋值，所以只能声明为指针）
    QOpenGLTexture *texture1{ nullptr };
    QOpenGLTexture *texture2{ nullptr };
    //定时器，做箱子旋转动画
    QTimer timer;
    int rotate{ 0 };

    //操作View，我这里为了展示没有封装成单独的Camera类
    //Camera Attributes
    QVector3D cameraPosition{ 0.0f, 0.0f, 3.0f };
    QVector3D cameraFront{ -cameraPosition };
    QVector3D cameraUp{ 0.0f, 1.0f, 0.0f };
    QVector3D cameraRight{ };
    QVector3D cameraWorldUp{ cameraUp };
    //Euler Angles
    //偏航角如果是0.0f,指向的是 x轴正方向，即右方向，所以向里转90度，初始方向指向z轴负方向
    //（这里有个问题，教程是90，但是算出来整体向右偏移了）
    float eulerYaw{ -89.5f }; //x偏航角
    float eulerPitch{ 0.0f }; //y俯仰角
    //Camera options
    float cameraSpeed{ 2.0f };
    float cameraSensitivity{ 0.01f };
    float projectionFovy{ 45.0f }; //透视投影的fovy参数
    //鼠标位置
    QPoint mousePos;
};