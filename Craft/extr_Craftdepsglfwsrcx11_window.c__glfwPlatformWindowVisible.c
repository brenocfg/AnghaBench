#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {TYPE_2__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_11__ {scalar_t__ map_state; } ;
typedef  TYPE_4__ XWindowAttributes ;
struct TYPE_8__ {int /*<<< orphan*/  display; } ;
struct TYPE_12__ {TYPE_1__ x11; } ;

/* Variables and functions */
 scalar_t__ IsViewable ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_6__ _glfw ; 

int _glfwPlatformWindowVisible(_GLFWwindow* window)
{
    XWindowAttributes wa;
    XGetWindowAttributes(_glfw.x11.display, window->x11.handle, &wa);
    return wa.map_state == IsViewable;
}