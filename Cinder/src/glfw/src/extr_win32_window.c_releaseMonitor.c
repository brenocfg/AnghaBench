#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* monitor; } ;
typedef  TYPE_1__ _GLFWwindow ;
struct TYPE_6__ {TYPE_1__* window; } ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwInputMonitorWindowChange (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwRestoreVideoModeWin32 (TYPE_3__*) ; 

__attribute__((used)) static void releaseMonitor(_GLFWwindow* window)
{
    if (window->monitor->window != window)
        return;

    _glfwInputMonitorWindowChange(window->monitor, NULL);
    _glfwRestoreVideoModeWin32(window->monitor);
}