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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {int /*<<< orphan*/  errorCode; int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGetErrorText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int,char*,char const*,char*) ; 

void _glfwInputErrorX11(int error, const char* message)
{
    char buffer[8192];
    XGetErrorText(_glfw.x11.display, _glfw.x11.errorCode,
                  buffer, sizeof(buffer));

    _glfwInputError(error, "%s: %s", message, buffer);
}