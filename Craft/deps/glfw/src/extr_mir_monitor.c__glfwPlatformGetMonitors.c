#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ cur_mode; int /*<<< orphan*/  output_id; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {int /*<<< orphan*/  modeCount; int /*<<< orphan*/  modes; TYPE_2__ mir; } ;
typedef  TYPE_3__ _GLFWmonitor ;
struct TYPE_19__ {int num_outputs; TYPE_4__* outputs; } ;
struct TYPE_18__ {scalar_t__ num_modes; scalar_t__ current_mode; int /*<<< orphan*/  output_id; int /*<<< orphan*/  position_y; int /*<<< orphan*/  position_x; int /*<<< orphan*/  physical_height_mm; int /*<<< orphan*/  physical_width_mm; scalar_t__ connected; scalar_t__ used; } ;
struct TYPE_15__ {int /*<<< orphan*/  connection; } ;
struct TYPE_14__ {TYPE_1__ mir; } ;
typedef  TYPE_4__ MirDisplayOutput ;
typedef  TYPE_5__ MirDisplayConfiguration ;

/* Variables and functions */
 TYPE_13__ _glfw ; 
 TYPE_3__* _glfwAllocMonitor (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoModes (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* mir_connection_create_display_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_display_config_destroy (TYPE_5__*) ; 
 TYPE_3__** realloc (TYPE_3__**,int) ; 

_GLFWmonitor** _glfwPlatformGetMonitors(int* count)
{
    int i, found = 0;
    _GLFWmonitor** monitors = NULL;
    MirDisplayConfiguration* displayConfig =
        mir_connection_create_display_config(_glfw.mir.connection);

    *count = 0;

    for (i = 0;  i < displayConfig->num_outputs;  i++)
    {
        const MirDisplayOutput* out = displayConfig->outputs + i;

        if (out->used &&
            out->connected &&
            out->num_modes &&
            out->current_mode < out->num_modes)
        {
            found++;
            monitors        = realloc(monitors, sizeof(_GLFWmonitor*) * found);
            monitors[i]     = _glfwAllocMonitor("Unknown",
                                                out->physical_width_mm,
                                                out->physical_height_mm);

            monitors[i]->mir.x         = out->position_x;
            monitors[i]->mir.y         = out->position_y;
            monitors[i]->mir.output_id = out->output_id;
            monitors[i]->mir.cur_mode  = out->current_mode;

            monitors[i]->modes = _glfwPlatformGetVideoModes(monitors[i],
                                                            &monitors[i]->modeCount);
        }
    }

    mir_display_config_destroy(displayConfig);

    *count = found;
    return monitors;
}