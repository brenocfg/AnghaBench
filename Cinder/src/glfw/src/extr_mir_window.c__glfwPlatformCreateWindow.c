#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_2__ _GLFWwndconfig ;
struct TYPE_13__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  surface; int /*<<< orphan*/  window; } ;
struct TYPE_15__ {TYPE_1__ mir; scalar_t__ monitor; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
struct TYPE_16__ {scalar_t__ client; } ;
typedef  TYPE_4__ _GLFWctxconfig ;
struct TYPE_17__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_5__ GLFWvidmode ;

/* Variables and functions */
 int GLFW_FALSE ; 
 scalar_t__ GLFW_NO_API ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwCreateContextEGL (TYPE_3__*,TYPE_4__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _glfwInitEGL () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoMode (scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  createSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  mir_buffer_stream_get_egl_native_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_get_buffer_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mir_surface_state_fullscreen ; 

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    if (window->monitor)
    {
        GLFWvidmode mode;
        _glfwPlatformGetVideoMode(window->monitor, &mode);

        mir_surface_set_state(window->mir.surface, mir_surface_state_fullscreen);

        if (wndconfig->width > mode.width || wndconfig->height > mode.height)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Mir: Requested surface size too large: %ix%i",
                            wndconfig->width, wndconfig->height);

            return GLFW_FALSE;
        }
    }

    window->mir.width  = wndconfig->width;
    window->mir.height = wndconfig->height;

    if (!createSurface(window))
        return GLFW_FALSE;

    window->mir.window = mir_buffer_stream_get_egl_native_window(
                                   mir_surface_get_buffer_stream(window->mir.surface));

    if (ctxconfig->client != GLFW_NO_API)
    {
        if (!_glfwInitEGL())
            return GLFW_FALSE;
        if (!_glfwCreateContextEGL(window, ctxconfig, fbconfig))
            return GLFW_FALSE;
    }

    return GLFW_TRUE;
}