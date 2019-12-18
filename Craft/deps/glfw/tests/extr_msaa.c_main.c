#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_SAMPLES ; 
 int /*<<< orphan*/  GLFW_VISIBLE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int GL_FALSE ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_MULTISAMPLE_ARB ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_SAMPLES_ARB ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_size_callback ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glOrtho (float,float,float,float,float,float) ; 
 int /*<<< orphan*/  glRectf (float,float,float,float) ; 
 int /*<<< orphan*/  glRotatef (int /*<<< orphan*/ ,float,float,float) ; 
 int /*<<< orphan*/  glTranslatef (float,float,float) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwExtensionSupported (char*) ; 
 int /*<<< orphan*/  glfwGetTime () ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwShowWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char** argv)
{
    int ch, samples = 4;
    GLFWwindow* window;

    while ((ch = getopt(argc, argv, "hs:")) != -1)
    {
        switch (ch)
        {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 's':
                samples = atoi(optarg);
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    if (samples)
        printf("Requesting MSAA with %i samples\n", samples);
    else
        printf("Requesting that MSAA not be available\n");

    glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    window = glfwCreateWindow(800, 400, "Aliasing Detector", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!glfwExtensionSupported("GL_ARB_multisample"))
    {
        printf("GL_ARB_multisample extension not supported\n");

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwShowWindow(window);

    glGetIntegerv(GL_SAMPLES_ARB, &samples);
    if (samples)
        printf("Context reports MSAA is available with %i samples\n", samples);
    else
        printf("Context reports MSAA is unavailable\n");

    glMatrixMode(GL_PROJECTION);
    glOrtho(0.f, 1.f, 0.f, 0.5f, 0.f, 1.f);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window))
    {
        GLfloat time = (GLfloat) glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.25f, 0.25f, 0.f);
        glRotatef(time, 0.f, 0.f, 1.f);

        glDisable(GL_MULTISAMPLE_ARB);
        glRectf(-0.15f, -0.15f, 0.15f, 0.15f);

        glLoadIdentity();
        glTranslatef(0.75f, 0.25f, 0.f);
        glRotatef(time, 0.f, 0.f, 1.f);

        glEnable(GL_MULTISAMPLE_ARB);
        glRectf(-0.15f, -0.15f, 0.15f, 0.15f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}