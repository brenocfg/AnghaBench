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
struct TYPE_4__ {int /*<<< orphan*/  dc; int /*<<< orphan*/  interval; } ;
struct TYPE_5__ {TYPE_1__ wgl; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  SwapBuffers (int /*<<< orphan*/ ) ; 
 scalar_t__ _glfwIsCompositionEnabled () ; 
 int /*<<< orphan*/  _glfw_DwmFlush () ; 
 int abs (int /*<<< orphan*/ ) ; 

void _glfwPlatformSwapBuffers(_GLFWwindow* window)
{
    // HACK: Use DwmFlush when desktop composition is enabled
    if (_glfwIsCompositionEnabled() && !window->monitor)
    {
        int count = abs(window->wgl.interval);
        while (count--)
            _glfw_DwmFlush();
    }

    SwapBuffers(window->wgl.dc);
}