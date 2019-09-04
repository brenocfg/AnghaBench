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
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_1__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ _glfw ; 

void _glfwPlatformUnhideWindow(_GLFWwindow* window)
{
    XMapWindow(_glfw.x11.display, window->x11.handle);
    XFlush(_glfw.x11.display);
}