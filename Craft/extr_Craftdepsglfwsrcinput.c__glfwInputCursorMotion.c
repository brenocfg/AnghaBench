#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* cursorPos ) (int /*<<< orphan*/ *,double,double) ;} ;
struct TYPE_5__ {scalar_t__ cursorMode; double cursorPosX; double cursorPosY; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,double,double) ; 

void _glfwInputCursorMotion(_GLFWwindow* window, double x, double y)
{
    if (window->cursorMode == GLFW_CURSOR_DISABLED)
    {
        if (x == 0.0 && y == 0.0)
            return;

        window->cursorPosX += x;
        window->cursorPosY += y;

        x = window->cursorPosX;
        y = window->cursorPosY;
    }

    if (window->callbacks.cursorPos)
        window->callbacks.cursorPos((GLFWwindow*) window, x, y);
}