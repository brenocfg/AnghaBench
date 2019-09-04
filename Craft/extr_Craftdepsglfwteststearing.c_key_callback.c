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
#define  GLFW_KEY_DOWN 130 
#define  GLFW_KEY_ESCAPE 129 
#define  GLFW_KEY_UP 128 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_swap_interval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_interval ; 
 int /*<<< orphan*/  swap_tear ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_UP:
        {
            if (swap_interval + 1 > swap_interval)
                set_swap_interval(window, swap_interval + 1);
            break;
        }

        case GLFW_KEY_DOWN:
        {
            if (swap_tear)
            {
                if (swap_interval - 1 < swap_interval)
                    set_swap_interval(window, swap_interval - 1);
            }
            else
            {
                if (swap_interval - 1 >= 0)
                    set_swap_interval(window, swap_interval - 1);
            }
            break;
        }

        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, 1);
            break;
    }
}