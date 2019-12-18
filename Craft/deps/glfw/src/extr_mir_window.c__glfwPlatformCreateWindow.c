#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ width; scalar_t__ height; scalar_t__ monitor; } ;
typedef  TYPE_2__ _GLFWwndconfig ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  surface; int /*<<< orphan*/  window; } ;
struct TYPE_12__ {TYPE_1__ mir; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
typedef  int /*<<< orphan*/  _GLFWctxconfig ;
struct TYPE_13__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_4__ GLFWvidmode ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  _glfwCreateContext (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoMode (scalar_t__,TYPE_4__*) ; 
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
    if (!_glfwCreateContext(window, ctxconfig, fbconfig))
        return GL_FALSE;

    if (wndconfig->monitor)
    {
        GLFWvidmode mode;
        _glfwPlatformGetVideoMode(wndconfig->monitor, &mode);

        mir_surface_set_state(window->mir.surface, mir_surface_state_fullscreen);

        if (wndconfig->width > mode.width || wndconfig->height > mode.height)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Mir: Requested surface size too large: %ix%i",
                            wndconfig->width, wndconfig->height);

            return GL_FALSE;
        }
    }

    window->mir.width  = wndconfig->width;
    window->mir.height = wndconfig->height;

    if (!createSurface(window))
        return GL_FALSE;

    window->mir.window = mir_buffer_stream_get_egl_native_window(
                                   mir_surface_get_buffer_stream(window->mir.surface));

    return GL_TRUE;
}