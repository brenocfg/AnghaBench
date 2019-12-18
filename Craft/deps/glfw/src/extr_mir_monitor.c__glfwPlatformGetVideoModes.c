#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ output_id; } ;
struct TYPE_19__ {TYPE_2__ mir; } ;
typedef  TYPE_4__ _GLFWmonitor ;
struct TYPE_22__ {int /*<<< orphan*/  refreshRate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_21__ {int num_outputs; TYPE_5__* outputs; } ;
struct TYPE_20__ {scalar_t__ output_id; int num_modes; int /*<<< orphan*/ * output_formats; TYPE_3__* modes; } ;
struct TYPE_18__ {int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  vertical_resolution; int /*<<< orphan*/  horizontal_resolution; } ;
struct TYPE_16__ {int /*<<< orphan*/  connection; } ;
struct TYPE_15__ {TYPE_1__ mir; } ;
typedef  TYPE_5__ MirDisplayOutput ;
typedef  TYPE_6__ MirDisplayConfiguration ;
typedef  TYPE_7__ GLFWvidmode ;

/* Variables and functions */
 int /*<<< orphan*/  FillInRGBBitsFromPixelFormat (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_13__ _glfw ; 
 TYPE_7__* calloc (int,int) ; 
 TYPE_6__* mir_connection_create_display_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_display_config_destroy (TYPE_6__*) ; 

GLFWvidmode* _glfwPlatformGetVideoModes(_GLFWmonitor* monitor, int* found)
{
    int i;
    GLFWvidmode* modes = NULL;
    MirDisplayConfiguration* displayConfig =
        mir_connection_create_display_config(_glfw.mir.connection);

    for (i = 0;  i < displayConfig->num_outputs;  i++)
    {
        const MirDisplayOutput* out = displayConfig->outputs + i;
        if (out->output_id != monitor->mir.output_id)
            continue;

        modes = calloc(out->num_modes, sizeof(GLFWvidmode));

        for (*found = 0;  *found < out->num_modes;  (*found)++)
        {
            modes[*found].width  = out->modes[*found].horizontal_resolution;
            modes[*found].height = out->modes[*found].vertical_resolution;
            modes[*found].refreshRate = out->modes[*found].refresh_rate;

            FillInRGBBitsFromPixelFormat(&modes[*found], out->output_formats[*found]);
        }

        break;
    }

    mir_display_config_destroy(displayConfig);

    return modes;
}