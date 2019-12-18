#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct wl_output {int dummy; } ;
typedef  int /*<<< orphan*/  name_str ;
typedef  int /*<<< orphan*/  _GLFWvidmodeWayland ;
struct TYPE_10__ {int modesSize; int scale; struct wl_output* output; int /*<<< orphan*/  modes; } ;
struct TYPE_12__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWmonitor ;
struct TYPE_11__ {int monitorsCount; int monitorsSize; TYPE_3__** monitors; int /*<<< orphan*/  registry; } ;
struct TYPE_13__ {TYPE_2__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_9__ _glfw ; 
 TYPE_3__* _glfwAllocMonitor (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwFreeMonitor (TYPE_3__*) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_listener ; 
 TYPE_3__** realloc (TYPE_3__**,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  wl_output_add_listener (struct wl_output*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  wl_output_interface ; 
 struct wl_output* wl_registry_bind (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

void _glfwAddOutputWayland(uint32_t name, uint32_t version)
{
    _GLFWmonitor *monitor;
    struct wl_output *output;
    char name_str[80];

    memset(name_str, 0, sizeof(name_str));
    snprintf(name_str, 79, "wl_output@%u", name);

    if (version < 2)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Unsupported output interface version");
        return;
    }

    monitor = _glfwAllocMonitor(name_str, 0, 0);

    output = wl_registry_bind(_glfw.wl.registry,
                              name,
                              &wl_output_interface,
                              2);
    if (!output)
    {
        _glfwFreeMonitor(monitor);
        return;
    }

    monitor->wl.modes = calloc(4, sizeof(_GLFWvidmodeWayland));
    monitor->wl.modesSize = 4;

    monitor->wl.scale = 1;

    monitor->wl.output = output;
    wl_output_add_listener(output, &output_listener, monitor);

    if (_glfw.wl.monitorsCount + 1 >= _glfw.wl.monitorsSize)
    {
        _GLFWmonitor** monitors = _glfw.wl.monitors;
        int size = _glfw.wl.monitorsSize * 2;

        monitors = realloc(monitors, size * sizeof(_GLFWmonitor*));

        _glfw.wl.monitors = monitors;
        _glfw.wl.monitorsSize = size;
    }

    _glfw.wl.monitors[_glfw.wl.monitorsCount++] = monitor;
}