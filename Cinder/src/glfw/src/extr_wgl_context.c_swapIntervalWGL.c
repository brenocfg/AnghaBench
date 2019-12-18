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
struct TYPE_7__ {int interval; } ;
struct TYPE_8__ {TYPE_1__ wgl; } ;
struct TYPE_10__ {int /*<<< orphan*/  monitor; TYPE_2__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_9__ {int /*<<< orphan*/  (* SwapIntervalEXT ) (int) ;scalar_t__ EXT_swap_control; } ;
struct TYPE_11__ {TYPE_3__ wgl; } ;

/* Variables and functions */
 TYPE_6__ _glfw ; 
 TYPE_4__* _glfwPlatformGetCurrentContext () ; 
 scalar_t__ isCompositionEnabled () ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void swapIntervalWGL(int interval)
{
    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    window->context.wgl.interval = interval;

    // HACK: Disable WGL swap interval when desktop composition is enabled to
    //       avoid interfering with DWM vsync
    if (isCompositionEnabled() && !window->monitor)
        interval = 0;

    if (_glfw.wgl.EXT_swap_control)
        _glfw.wgl.SwapIntervalEXT(interval);
}