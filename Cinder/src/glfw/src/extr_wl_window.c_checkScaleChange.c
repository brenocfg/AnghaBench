#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int monitorsCount; int scale; int width; int height; int /*<<< orphan*/  native; int /*<<< orphan*/  surface; TYPE_3__** monitors; } ;
struct TYPE_13__ {TYPE_4__ wl; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_9__ {int wl_compositor_version; } ;
struct TYPE_14__ {TYPE_1__ wl; } ;
struct TYPE_10__ {int scale; } ;
struct TYPE_11__ {TYPE_2__ wl; } ;

/* Variables and functions */
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwInputFramebufferSize (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  wl_egl_window_resize (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void checkScaleChange(_GLFWwindow* window)
{
    int scaledWidth, scaledHeight;
    int scale = 1;
    int i;
    int monitorScale;

    // Check if we will be able to set the buffer scale or not.
    if (_glfw.wl.wl_compositor_version < 3)
        return;

    // Get the scale factor from the highest scale monitor.
    for (i = 0; i < window->wl.monitorsCount; ++i)
    {
        monitorScale = window->wl.monitors[i]->wl.scale;
        if (scale < monitorScale)
            scale = monitorScale;
    }

    // Only change the framebuffer size if the scale changed.
    if (scale != window->wl.scale)
    {
        window->wl.scale = scale;
        scaledWidth = window->wl.width * scale;
        scaledHeight = window->wl.height * scale;
        wl_surface_set_buffer_scale(window->wl.surface, scale);
        wl_egl_window_resize(window->wl.native, scaledWidth, scaledHeight, 0, 0);
        _glfwInputFramebufferSize(window, scaledWidth, scaledHeight);
    }
}