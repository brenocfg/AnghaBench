#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ display; scalar_t__ registry; scalar_t__ cursorSurface; scalar_t__ cursorTheme; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwTerminateEGL () ; 
 int /*<<< orphan*/  _glfwTerminateJoysticksLinux () ; 
 int /*<<< orphan*/  _glfwTerminateThreadLocalStoragePOSIX () ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_flush (scalar_t__) ; 
 int /*<<< orphan*/  wl_registry_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_surface_destroy (scalar_t__) ; 

void _glfwPlatformTerminate(void)
{
    _glfwTerminateEGL();
    _glfwTerminateJoysticksLinux();
    _glfwTerminateThreadLocalStoragePOSIX();

    if (_glfw.wl.cursorTheme)
        wl_cursor_theme_destroy(_glfw.wl.cursorTheme);
    if (_glfw.wl.cursorSurface)
        wl_surface_destroy(_glfw.wl.cursorSurface);
    if (_glfw.wl.registry)
        wl_registry_destroy(_glfw.wl.registry);
    if (_glfw.wl.display)
        wl_display_flush(_glfw.wl.display);
    if (_glfw.wl.display)
        wl_display_disconnect(_glfw.wl.display);
}