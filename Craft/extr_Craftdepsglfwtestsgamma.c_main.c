#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  blueBits; int /*<<< orphan*/  greenBits; int /*<<< orphan*/  redBits; int /*<<< orphan*/  refreshRate; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_BLUE_BITS ; 
 int /*<<< orphan*/  GLFW_GREEN_BITS ; 
 int /*<<< orphan*/  GLFW_RED_BITS ; 
 int /*<<< orphan*/  GLFW_REFRESH_RATE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_size_callback ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor3f (float,float,float) ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glOrtho (float,float,float,float,float,float) ; 
 int /*<<< orphan*/  glRectf (float,float,float,float) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEvents () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  set_gamma (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char** argv)
{
    int width, height, ch;
    GLFWmonitor* monitor = NULL;
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    while ((ch = getopt(argc, argv, "fh")) != -1)
    {
        switch (ch)
        {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            case 'f':
                monitor = glfwGetPrimaryMonitor();
                break;

            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    if (monitor)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

        width = mode->width;
        height = mode->height;
    }
    else
    {
        width = 200;
        height = 200;
    }

    window = glfwCreateWindow(width, height, "Gamma Test", monitor, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    set_gamma(window, 1.f);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.5f, 0.5f, 0.5f, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.8f, 0.2f, 0.4f);
        glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}