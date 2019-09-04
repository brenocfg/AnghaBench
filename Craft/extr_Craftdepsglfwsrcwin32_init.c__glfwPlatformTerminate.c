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
struct TYPE_3__ {int /*<<< orphan*/  clipboardString; int /*<<< orphan*/  foregroundLockTimeout; } ;
struct TYPE_4__ {TYPE_1__ win32; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIF_SENDCHANGE ; 
 int /*<<< orphan*/  SPI_SETFOREGROUNDLOCKTIMEOUT ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIntToPtr (int /*<<< orphan*/ ) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwTerminateContextAPI () ; 
 int /*<<< orphan*/  _glfwTerminateJoysticks () ; 
 int /*<<< orphan*/  _glfwUnregisterWindowClass () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminateLibraries () ; 

void _glfwPlatformTerminate(void)
{
    _glfwUnregisterWindowClass();

    // Restore previous foreground lock timeout system setting
    SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0,
                          UIntToPtr(_glfw.win32.foregroundLockTimeout),
                          SPIF_SENDCHANGE);

    free(_glfw.win32.clipboardString);

    _glfwTerminateJoysticks();
    _glfwTerminateContextAPI();
    terminateLibraries();
}