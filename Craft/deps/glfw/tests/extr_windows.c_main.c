#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  scalar_t__ GLboolean ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_DECORATED ; 
 int /*<<< orphan*/  GLFW_VISIBLE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_TRUE ; 
 TYPE_1__* colors ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowFrameSize (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowPos (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  glfwShowWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/ * titles ; 

int main(int argc, char** argv)
{
    int i;
    GLboolean running = GL_TRUE;
    GLFWwindow* windows[4];

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    for (i = 0;  i < 4;  i++)
    {
        int left, top, right, bottom;

        windows[i] = glfwCreateWindow(200, 200, titles[i], NULL, NULL);
        if (!windows[i])
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(windows[i], key_callback);

        glfwMakeContextCurrent(windows[i]);
        glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);

        glfwGetWindowFrameSize(windows[i], &left, &top, &right, &bottom);
        glfwSetWindowPos(windows[i],
                         100 + (i & 1) * (200 + left + right),
                         100 + (i >> 1) * (200 + top + bottom));
    }

    for (i = 0;  i < 4;  i++)
        glfwShowWindow(windows[i]);

    while (running)
    {
        for (i = 0;  i < 4;  i++)
        {
            glfwMakeContextCurrent(windows[i]);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(windows[i]);

            if (glfwWindowShouldClose(windows[i]))
                running = GL_FALSE;
        }

        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}