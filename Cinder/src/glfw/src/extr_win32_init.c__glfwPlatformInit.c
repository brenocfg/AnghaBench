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
struct TYPE_3__ {int /*<<< orphan*/  helperWindowHandle; int /*<<< orphan*/  foregroundLockTimeout; } ;
struct TYPE_4__ {TYPE_1__ win32; } ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  PROCESS_PER_MONITOR_DPI_AWARE ; 
 int /*<<< orphan*/  SPIF_SENDCHANGE ; 
 int /*<<< orphan*/  SPI_GETFOREGROUNDLOCKTIMEOUT ; 
 int /*<<< orphan*/  SPI_SETFOREGROUNDLOCKTIMEOUT ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UIntToPtr (int /*<<< orphan*/ ) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInitJoysticksWin32 () ; 
 int /*<<< orphan*/  _glfwInitThreadLocalStorageWin32 () ; 
 int /*<<< orphan*/  _glfwInitTimerWin32 () ; 
 int /*<<< orphan*/  _glfwPlatformPollEvents () ; 
 int /*<<< orphan*/  _glfwRegisterWindowClassWin32 () ; 
 int /*<<< orphan*/  _glfw_SetProcessDPIAware () ; 
 int /*<<< orphan*/  _glfw_SetProcessDpiAwareness (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  createHelperWindow () ; 
 int /*<<< orphan*/  createKeyTables () ; 
 int /*<<< orphan*/  loadLibraries () ; 

int _glfwPlatformInit(void)
{
    if (!_glfwInitThreadLocalStorageWin32())
        return GLFW_FALSE;

    // To make SetForegroundWindow work as we want, we need to fiddle
    // with the FOREGROUNDLOCKTIMEOUT system setting (we do this as early
    // as possible in the hope of still being the foreground process)
    SystemParametersInfoW(SPI_GETFOREGROUNDLOCKTIMEOUT, 0,
                          &_glfw.win32.foregroundLockTimeout, 0);
    SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, UIntToPtr(0),
                          SPIF_SENDCHANGE);

    if (!loadLibraries())
        return GLFW_FALSE;

    createKeyTables();

    if (_glfw_SetProcessDpiAwareness)
        _glfw_SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    else if (_glfw_SetProcessDPIAware)
        _glfw_SetProcessDPIAware();

    if (!_glfwRegisterWindowClassWin32())
        return GLFW_FALSE;

    _glfw.win32.helperWindowHandle = createHelperWindow();
    if (!_glfw.win32.helperWindowHandle)
        return GLFW_FALSE;

    _glfwPlatformPollEvents();

    _glfwInitTimerWin32();
    _glfwInitJoysticksWin32();

    return GLFW_TRUE;
}