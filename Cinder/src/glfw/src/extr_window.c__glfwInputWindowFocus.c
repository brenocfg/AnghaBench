#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* focus ) (int /*<<< orphan*/ *,scalar_t__) ;} ;
struct TYPE_7__ {scalar_t__* keys; scalar_t__* mouseButtons; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 int GLFW_KEY_LAST ; 
 int GLFW_MOUSE_BUTTON_LAST ; 
 scalar_t__ GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 int /*<<< orphan*/  _glfwInputKey (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputMouseClick (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__) ; 

void _glfwInputWindowFocus(_GLFWwindow* window, GLFWbool focused)
{
    if (focused)
    {
        if (window->callbacks.focus)
            window->callbacks.focus((GLFWwindow*) window, focused);
    }
    else
    {
        int i;

        if (window->callbacks.focus)
            window->callbacks.focus((GLFWwindow*) window, focused);

        // Release all pressed keyboard keys
        for (i = 0;  i <= GLFW_KEY_LAST;  i++)
        {
            if (window->keys[i] == GLFW_PRESS)
                _glfwInputKey(window, i, 0, GLFW_RELEASE, 0);
        }

        // Release all pressed mouse buttons
        for (i = 0;  i <= GLFW_MOUSE_BUTTON_LAST;  i++)
        {
            if (window->mouseButtons[i] == GLFW_PRESS)
                _glfwInputMouseClick(window, i, GLFW_RELEASE, 0);
        }
    }
}