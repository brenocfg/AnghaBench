#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  handle; } ;
struct TYPE_22__ {TYPE_4__ x11; TYPE_10__* monitor; int /*<<< orphan*/  videoMode; } ;
typedef  TYPE_6__ _GLFWwindow ;
struct TYPE_23__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_18__ {scalar_t__ available; } ;
struct TYPE_17__ {scalar_t__ count; int /*<<< orphan*/  exposure; int /*<<< orphan*/  blanking; int /*<<< orphan*/  interval; int /*<<< orphan*/  timeout; } ;
struct TYPE_21__ {int NET_WM_STATE_FULLSCREEN; scalar_t__ NET_WM_STATE; int /*<<< orphan*/  display; scalar_t__ NET_ACTIVE_WINDOW; scalar_t__ NET_WM_FULLSCREEN_MONITORS; TYPE_2__ xinerama; scalar_t__ NET_WM_BYPASS_COMPOSITOR; TYPE_1__ saver; } ;
struct TYPE_19__ {int index; } ;
struct TYPE_16__ {TYPE_5__ x11; } ;
struct TYPE_15__ {TYPE_3__ x11; } ;
typedef  TYPE_7__ GLFWvidmode ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  DefaultExposures ; 
 int /*<<< orphan*/  DontPreferBlanking ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  RevertToParent ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XGetScreenSaver (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMoveResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRaiseWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetInputFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetScreenSaver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _NET_WM_STATE_ADD ; 
 TYPE_14__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformGetMonitorPos (TYPE_10__*,int*,int*) ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoMode (TYPE_10__*,TYPE_7__*) ; 
 int /*<<< orphan*/  _glfwSetVideoMode (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendEventToWM (TYPE_6__*,scalar_t__,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enterFullscreenMode(_GLFWwindow* window)
{
    if (_glfw.x11.saver.count == 0)
    {
        // Remember old screen saver settings
        XGetScreenSaver(_glfw.x11.display,
                        &_glfw.x11.saver.timeout,
                        &_glfw.x11.saver.interval,
                        &_glfw.x11.saver.blanking,
                        &_glfw.x11.saver.exposure);

        // Disable screen saver
        XSetScreenSaver(_glfw.x11.display, 0, 0, DontPreferBlanking,
                        DefaultExposures);
    }

    _glfw.x11.saver.count++;

    _glfwSetVideoMode(window->monitor, &window->videoMode);

    if (_glfw.x11.NET_WM_BYPASS_COMPOSITOR)
    {
        const unsigned long value = 1;

        XChangeProperty(_glfw.x11.display,  window->x11.handle,
                        _glfw.x11.NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                        PropModeReplace, (unsigned char*) &value, 1);
    }

    // Position the window over its monitor
    {
        int xpos, ypos;
        GLFWvidmode mode;

        _glfwPlatformGetMonitorPos(window->monitor, &xpos, &ypos);
        _glfwPlatformGetVideoMode(window->monitor, &mode);

        XMoveResizeWindow(_glfw.x11.display, window->x11.handle,
                          xpos, ypos, mode.width, mode.height);
    }

    if (_glfw.x11.xinerama.available && _glfw.x11.NET_WM_FULLSCREEN_MONITORS)
    {
        sendEventToWM(window,
                      _glfw.x11.NET_WM_FULLSCREEN_MONITORS,
                      window->monitor->x11.index,
                      window->monitor->x11.index,
                      window->monitor->x11.index,
                      window->monitor->x11.index,
                      0);
    }

    if (_glfw.x11.NET_ACTIVE_WINDOW)
    {
        // Ask the window manager to raise and focus the GLFW window
        // Only focused windows with the _NET_WM_STATE_FULLSCREEN state end up
        // on top of all other windows ("Stacking order" in EWMH spec)
        sendEventToWM(window, _glfw.x11.NET_ACTIVE_WINDOW, 1, 0, 0, 0, 0);
    }
    else
    {
        XRaiseWindow(_glfw.x11.display, window->x11.handle);
        XSetInputFocus(_glfw.x11.display, window->x11.handle,
                       RevertToParent, CurrentTime);
    }

    if (_glfw.x11.NET_WM_STATE && _glfw.x11.NET_WM_STATE_FULLSCREEN)
    {
        // Ask the window manager to make the GLFW window a full screen window
        // Full screen windows are undecorated and, when focused, are kept
        // on top of all other windows
        sendEventToWM(window,
                      _glfw.x11.NET_WM_STATE,
                      _NET_WM_STATE_ADD,
                      _glfw.x11.NET_WM_STATE_FULLSCREEN,
                      0, 1, 0);
    }
}