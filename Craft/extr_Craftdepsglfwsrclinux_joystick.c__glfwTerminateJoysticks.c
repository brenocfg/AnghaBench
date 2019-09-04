#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ inotify; scalar_t__ watch; int /*<<< orphan*/  regex; TYPE_1__* js; } ;
struct TYPE_6__ {TYPE_2__ linux_js; } ;
struct TYPE_4__ {scalar_t__ fd; int /*<<< orphan*/  path; int /*<<< orphan*/  name; int /*<<< orphan*/  buttons; int /*<<< orphan*/  axes; scalar_t__ present; } ;

/* Variables and functions */
 int GLFW_JOYSTICK_LAST ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_rm_watch (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

void _glfwTerminateJoysticks(void)
{
#if defined(__linux__)
    int i;

    for (i = 0;  i <= GLFW_JOYSTICK_LAST;  i++)
    {
        if (_glfw.linux_js.js[i].present)
        {
            close(_glfw.linux_js.js[i].fd);
            free(_glfw.linux_js.js[i].axes);
            free(_glfw.linux_js.js[i].buttons);
            free(_glfw.linux_js.js[i].name);
            free(_glfw.linux_js.js[i].path);
        }
    }

    regfree(&_glfw.linux_js.regex);

    if (_glfw.linux_js.inotify > 0)
    {
        if (_glfw.linux_js.watch > 0)
            inotify_rm_watch(_glfw.linux_js.inotify, _glfw.linux_js.watch);

        close(_glfw.linux_js.inotify);
    }
#endif // __linux__
}