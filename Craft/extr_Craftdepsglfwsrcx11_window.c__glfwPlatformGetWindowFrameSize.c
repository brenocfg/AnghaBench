#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {TYPE_1__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  XPointer ;
typedef  int /*<<< orphan*/  XEvent ;
struct TYPE_9__ {scalar_t__ NET_FRAME_EXTENTS; int /*<<< orphan*/  display; scalar_t__ NET_REQUEST_FRAME_EXTENTS; } ;
struct TYPE_11__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XCheckIfEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (long*) ; 
 TYPE_7__ _glfw ; 
 int _glfwGetWindowProperty (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 double _glfwPlatformGetTime () ; 
 int /*<<< orphan*/  _glfwPlatformWindowVisible (TYPE_3__*) ; 
 int /*<<< orphan*/  isFrameExtentsEvent ; 
 int /*<<< orphan*/  selectDisplayConnection (struct timeval*) ; 
 int /*<<< orphan*/  sendEventToWM (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _glfwPlatformGetWindowFrameSize(_GLFWwindow* window,
                                     int* left, int* top,
                                     int* right, int* bottom)
{
    long* extents = NULL;

    if (_glfw.x11.NET_FRAME_EXTENTS == None)
        return;

    if (!_glfwPlatformWindowVisible(window) &&
        _glfw.x11.NET_REQUEST_FRAME_EXTENTS)
    {
        double base;
        XEvent event;

        // Ensure _NET_FRAME_EXTENTS is set, allowing glfwGetWindowFrameSize to
        // function before the window is mapped
        sendEventToWM(window, _glfw.x11.NET_REQUEST_FRAME_EXTENTS,
                      0, 0, 0, 0, 0);

        // HACK: Poll with timeout for the required reply instead of blocking
        //       This is done because some window managers (at least Unity,
        //       Fluxbox and Xfwm) failed to send the required reply
        //       They have been fixed but broken versions are still in the wild
        //       If you are affected by this and your window manager is NOT
        //       listed above, PLEASE report it to their and our issue trackers
        base = _glfwPlatformGetTime();
        while (!XCheckIfEvent(_glfw.x11.display,
                              &event,
                              isFrameExtentsEvent,
                              (XPointer) window))
        {
            double remaining;
            struct timeval timeout;

            remaining = 0.5 + base - _glfwPlatformGetTime();
            if (remaining <= 0.0)
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "X11: The window manager has a broken _NET_REQUEST_FRAME_EXTENTS implementation; please report this issue");
                return;
            }

            timeout.tv_sec = 0;
            timeout.tv_usec = (long) (remaining * 1e6);
            selectDisplayConnection(&timeout);
        }
    }

    if (_glfwGetWindowProperty(window->x11.handle,
                               _glfw.x11.NET_FRAME_EXTENTS,
                               XA_CARDINAL,
                               (unsigned char**) &extents) == 4)
    {
        if (left)
            *left = extents[0];
        if (top)
            *top = extents[2];
        if (right)
            *right = extents[1];
        if (bottom)
            *bottom = extents[3];
    }

    if (extents)
        XFree(extents);
}