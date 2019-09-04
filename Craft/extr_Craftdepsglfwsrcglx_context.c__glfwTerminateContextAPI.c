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
struct TYPE_3__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_4__ {TYPE_1__ glx; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwDestroyContextTLS () ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ *) ; 

void _glfwTerminateContextAPI(void)
{
    // NOTE: This function may not call any X11 functions, as it is called after
    //       XCloseDisplay (see _glfwPlatformTerminate for details)

    if (_glfw.glx.handle)
    {
        dlclose(_glfw.glx.handle);
        _glfw.glx.handle = NULL;
    }

    _glfwDestroyContextTLS();
}