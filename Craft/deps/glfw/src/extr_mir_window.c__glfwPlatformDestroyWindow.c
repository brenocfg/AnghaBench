#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * surface; } ;
struct TYPE_6__ {TYPE_1__ mir; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwDestroyContext (TYPE_2__*) ; 
 scalar_t__ mir_surface_is_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_surface_release_sync (int /*<<< orphan*/ *) ; 

void _glfwPlatformDestroyWindow(_GLFWwindow* window)
{
    if (mir_surface_is_valid(window->mir.surface))
    {
        mir_surface_release_sync(window->mir.surface);
        window->mir.surface = NULL;
    }

    _glfwDestroyContext(window);
}