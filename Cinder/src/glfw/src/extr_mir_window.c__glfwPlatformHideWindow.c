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
struct TYPE_7__ {int /*<<< orphan*/  surface; } ;
struct TYPE_8__ {TYPE_2__ mir; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_6__ {int /*<<< orphan*/  connection; } ;
struct TYPE_9__ {TYPE_1__ mir; } ;
typedef  int /*<<< orphan*/  MirSurfaceSpec ;

/* Variables and functions */
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/ * mir_connection_create_spec_for_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_apply_spec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_surface_spec_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_surface_spec_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_state_hidden ; 

void _glfwPlatformHideWindow(_GLFWwindow* window)
{
    MirSurfaceSpec* spec;

    spec = mir_connection_create_spec_for_changes(_glfw.mir.connection);
    mir_surface_spec_set_state(spec, mir_surface_state_hidden);

    mir_surface_apply_spec(window->mir.surface, spec);
    mir_surface_spec_release(spec);
}