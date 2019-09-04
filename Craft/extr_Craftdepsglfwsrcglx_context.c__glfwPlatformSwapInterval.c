#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {TYPE_2__ x11; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_9__ {int /*<<< orphan*/  (* SwapIntervalSGI ) (int) ;scalar_t__ SGI_swap_control; int /*<<< orphan*/  (* SwapIntervalMESA ) (int) ;scalar_t__ MESA_swap_control; int /*<<< orphan*/  (* SwapIntervalEXT ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ EXT_swap_control; } ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;
struct TYPE_11__ {TYPE_3__ glx; TYPE_1__ x11; } ;

/* Variables and functions */
 TYPE_6__ _glfw ; 
 TYPE_4__* _glfwPlatformGetCurrentContext () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  stub3 (int) ; 

void _glfwPlatformSwapInterval(int interval)
{
    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    if (_glfw.glx.EXT_swap_control)
    {
        _glfw.glx.SwapIntervalEXT(_glfw.x11.display,
                                  window->x11.handle,
                                  interval);
    }
    else if (_glfw.glx.MESA_swap_control)
        _glfw.glx.SwapIntervalMESA(interval);
    else if (_glfw.glx.SGI_swap_control)
    {
        if (interval > 0)
            _glfw.glx.SwapIntervalSGI(interval);
    }
}