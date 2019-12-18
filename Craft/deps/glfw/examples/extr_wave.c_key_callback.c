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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  GLFW_KEY_DOWN 135 
#define  GLFW_KEY_ESCAPE 134 
#define  GLFW_KEY_LEFT 133 
#define  GLFW_KEY_PAGE_DOWN 132 
#define  GLFW_KEY_PAGE_UP 131 
#define  GLFW_KEY_RIGHT 130 
#define  GLFW_KEY_SPACE 129 
#define  GLFW_KEY_UP 128 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int alpha ; 
 int beta ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_grid () ; 
 float zoom ; 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_SPACE:
            init_grid();
            break;
        case GLFW_KEY_LEFT:
            alpha += 5;
            break;
        case GLFW_KEY_RIGHT:
            alpha -= 5;
            break;
        case GLFW_KEY_UP:
            beta -= 5;
            break;
        case GLFW_KEY_DOWN:
            beta += 5;
            break;
        case GLFW_KEY_PAGE_UP:
            zoom -= 0.25f;
            if (zoom < 0.f)
                zoom = 0.f;
            break;
        case GLFW_KEY_PAGE_DOWN:
            zoom += 0.25f;
            break;
        default:
            break;
    }
}