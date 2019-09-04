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
struct TYPE_3__ {int /*<<< orphan*/ * display; int /*<<< orphan*/ * im; int /*<<< orphan*/  clipboardString; scalar_t__ cursor; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;
typedef  scalar_t__ Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCloseIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFreeCursor (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwTerminateContextAPI () ; 
 int /*<<< orphan*/  _glfwTerminateJoysticks () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void _glfwPlatformTerminate(void)
{
    if (_glfw.x11.cursor)
    {
        XFreeCursor(_glfw.x11.display, _glfw.x11.cursor);
        _glfw.x11.cursor = (Cursor) 0;
    }

    free(_glfw.x11.clipboardString);

    if (_glfw.x11.im)
    {
        XCloseIM(_glfw.x11.im);
        _glfw.x11.im = NULL;
    }

    _glfwTerminateJoysticks();

    if (_glfw.x11.display)
    {
        XCloseDisplay(_glfw.x11.display);
        _glfw.x11.display = NULL;
    }

    // NOTE: This needs to be done after XCloseDisplay, as libGL registers
    //       internal cleanup callbacks in libX11
    _glfwTerminateContextAPI();
}