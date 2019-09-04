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
#define  GLFW_KEY_ESCAPE 132 
#define  GLFW_KEY_KP_ADD 131 
#define  GLFW_KEY_KP_SUBTRACT 130 
#define  GLFW_KEY_Q 129 
#define  GLFW_KEY_W 128 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GL_TRUE ; 
 float STEP_SIZE ; 
 float gamma_value ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gamma (int /*<<< orphan*/ *,float) ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        }

        case GLFW_KEY_KP_ADD:
        case GLFW_KEY_Q:
        {
            set_gamma(window, gamma_value + STEP_SIZE);
            break;
        }

        case GLFW_KEY_KP_SUBTRACT:
        case GLFW_KEY_W:
        {
            if (gamma_value - STEP_SIZE > 0.f)
                set_gamma(window, gamma_value - STEP_SIZE);

            break;
        }
    }
}