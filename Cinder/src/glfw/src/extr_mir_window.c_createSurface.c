#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {TYPE_1__ mir; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  connection; } ;
struct TYPE_10__ {TYPE_2__ mir; } ;
typedef  int /*<<< orphan*/  MirSurfaceSpec ;
typedef  scalar_t__ MirPixelFormat ;
typedef  int /*<<< orphan*/  MirBufferUsage ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  addNewEvent ; 
 scalar_t__ findValidPixelFormat () ; 
 int /*<<< orphan*/  mir_buffer_usage_hardware ; 
 int /*<<< orphan*/ * mir_connection_create_spec_for_normal_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mir_pixel_format_invalid ; 
 int /*<<< orphan*/  mir_surface_create_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_surface_get_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_set_event_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mir_surface_spec_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_surface_spec_set_buffer_usage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_spec_set_name (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static GLFWbool createSurface(_GLFWwindow* window)
{
    MirSurfaceSpec* spec;
    MirBufferUsage buffer_usage = mir_buffer_usage_hardware;
    MirPixelFormat pixel_format = findValidPixelFormat();

    if (pixel_format == mir_pixel_format_invalid)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Mir: Unable to find a correct pixel format");
        return GLFW_FALSE;
    }
 
    spec = mir_connection_create_spec_for_normal_surface(_glfw.mir.connection,
                                                         window->mir.width,
                                                         window->mir.height,
                                                         pixel_format);

    mir_surface_spec_set_buffer_usage(spec, buffer_usage);
    mir_surface_spec_set_name(spec, "MirSurface");

    window->mir.surface = mir_surface_create_sync(spec);
    mir_surface_spec_release(spec);

    if (!mir_surface_is_valid(window->mir.surface))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Mir: Unable to create surface: %s",
                        mir_surface_get_error_message(window->mir.surface));

        return GLFW_FALSE;
    }

    mir_surface_set_event_handler(window->mir.surface, addNewEvent, window);

    return GLFW_TRUE;
}