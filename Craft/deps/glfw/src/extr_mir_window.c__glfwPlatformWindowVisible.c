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
struct TYPE_4__ {int /*<<< orphan*/  surface; } ;
struct TYPE_5__ {TYPE_1__ mir; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ mir_surface_get_visibility (int /*<<< orphan*/ ) ; 
 scalar_t__ mir_surface_visibility_exposed ; 

int _glfwPlatformWindowVisible(_GLFWwindow* window)
{
    return mir_surface_get_visibility(window->mir.surface) == mir_surface_visibility_exposed;
}