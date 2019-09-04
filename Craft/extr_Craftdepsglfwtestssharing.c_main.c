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
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int OFFSET ; 
 int /*<<< orphan*/  create_texture () ; 
 int /*<<< orphan*/  draw_quad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor3f (float,float,float) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEvents () ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_window (char*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ ** windows ; 

int main(int argc, char** argv)
{
    int x, y, width;
    GLuint texture;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    windows[0] = open_window("First", NULL, OFFSET, OFFSET);
    if (!windows[0])
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // This is the one and only time we create a texture
    // It is created inside the first context, created above
    // It will then be shared with the second context, created below
    texture = create_texture();

    glfwGetWindowPos(windows[0], &x, &y);
    glfwGetWindowSize(windows[0], &width, NULL);

    // Put the second window to the right of the first one
    windows[1] = open_window("Second", windows[0], x + width + OFFSET, y);
    if (!windows[1])
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Set drawing color for both contexts
    glfwMakeContextCurrent(windows[0]);
    glColor3f(0.6f, 0.f, 0.6f);
    glfwMakeContextCurrent(windows[1]);
    glColor3f(0.6f, 0.6f, 0.f);

    glfwMakeContextCurrent(windows[0]);

    while (!glfwWindowShouldClose(windows[0]) &&
           !glfwWindowShouldClose(windows[1]))
    {
        glfwMakeContextCurrent(windows[0]);
        draw_quad(texture);

        glfwMakeContextCurrent(windows[1]);
        draw_quad(texture);

        glfwSwapBuffers(windows[0]);
        glfwSwapBuffers(windows[1]);

        glfwWaitEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}