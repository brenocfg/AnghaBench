#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_pointer {int dummy; } ;
struct TYPE_7__ {void* cursorPosY; void* cursorPosX; } ;
struct TYPE_8__ {scalar_t__ cursorMode; TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_6__ {TYPE_3__* pointerFocus; } ;
struct TYPE_9__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputCursorMotion (TYPE_3__*,void*,void*) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 void* wl_fixed_to_double (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointerHandleMotion(void* data,
                                struct wl_pointer* pointer,
                                uint32_t time,
                                wl_fixed_t sx,
                                wl_fixed_t sy)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;

    if (!window)
        return;

    if (window->cursorMode == GLFW_CURSOR_DISABLED)
    {
        /* TODO */
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: GLFW_CURSOR_DISABLED not supported");
        return;
    }
    else
    {
        window->wl.cursorPosX = wl_fixed_to_double(sx);
        window->wl.cursorPosY = wl_fixed_to_double(sy);
    }

    _glfwInputCursorMotion(window,
                           wl_fixed_to_double(sx),
                           wl_fixed_to_double(sy));
}