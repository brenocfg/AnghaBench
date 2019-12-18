#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dc; int /*<<< orphan*/  interval; } ;
struct TYPE_6__ {TYPE_1__ wgl; } ;
struct TYPE_7__ {TYPE_2__ context; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  SwapBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfw_DwmFlush () ; 
 int abs (int /*<<< orphan*/ ) ; 
 scalar_t__ isCompositionEnabled () ; 

__attribute__((used)) static void swapBuffersWGL(_GLFWwindow* window)
{
    // HACK: Use DwmFlush when desktop composition is enabled
    if (isCompositionEnabled() && !window->monitor)
    {
        int count = abs(window->context.wgl.interval);
        while (count--)
            _glfw_DwmFlush();
    }

    SwapBuffers(window->context.wgl.dc);
}