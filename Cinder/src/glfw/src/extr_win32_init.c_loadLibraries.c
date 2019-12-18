#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XINPUTGETSTATE_T ;
typedef  scalar_t__ XINPUTGETCAPABILITIES_T ;
struct TYPE_14__ {void* instance; scalar_t__ SetProcessDpiAwareness; } ;
struct TYPE_13__ {void* instance; scalar_t__ DwmFlush; scalar_t__ DwmIsCompositionEnabled; } ;
struct TYPE_12__ {void* instance; scalar_t__ XInputGetState; scalar_t__ XInputGetCapabilities; } ;
struct TYPE_11__ {void* instance; scalar_t__ DirectInput8Create; } ;
struct TYPE_10__ {void* instance; scalar_t__ ChangeWindowMessageFilterEx; scalar_t__ SetProcessDPIAware; } ;
struct TYPE_9__ {void* instance; scalar_t__ timeGetTime; } ;
struct TYPE_15__ {TYPE_6__ shcore; TYPE_5__ dwmapi; TYPE_4__ xinput; TYPE_3__ dinput8; TYPE_2__ user32; TYPE_1__ winmm; } ;
struct TYPE_16__ {TYPE_7__ win32; } ;
typedef  scalar_t__ TIMEGETTIME_T ;
typedef  scalar_t__ SETPROCESSDPIAWARE_T ;
typedef  scalar_t__ SETPROCESSDPIAWARENESS_T ;
typedef  int /*<<< orphan*/  GLFWbool ;
typedef  scalar_t__ DWMISCOMPOSITIONENABLED_T ;
typedef  scalar_t__ DWMFLUSH_T ;
typedef  scalar_t__ DIRECTINPUT8CREATE_T ;
typedef  scalar_t__ CHANGEWINDOWMESSAGEFILTEREX_T ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ GetProcAddress (void*,char*) ; 
 void* LoadLibraryA (char const*) ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static GLFWbool loadLibraries(void)
{
    _glfw.win32.winmm.instance = LoadLibraryA("winmm.dll");
    if (!_glfw.win32.winmm.instance)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Win32: Failed to load winmm.dll");
        return GLFW_FALSE;
    }

    _glfw.win32.winmm.timeGetTime = (TIMEGETTIME_T)
        GetProcAddress(_glfw.win32.winmm.instance, "timeGetTime");

    _glfw.win32.user32.instance = LoadLibraryA("user32.dll");
    if (!_glfw.win32.user32.instance)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Win32: Failed to load user32.dll");
        return GLFW_FALSE;
    }

    _glfw.win32.user32.SetProcessDPIAware = (SETPROCESSDPIAWARE_T)
        GetProcAddress(_glfw.win32.user32.instance, "SetProcessDPIAware");
    _glfw.win32.user32.ChangeWindowMessageFilterEx = (CHANGEWINDOWMESSAGEFILTEREX_T)
        GetProcAddress(_glfw.win32.user32.instance, "ChangeWindowMessageFilterEx");

    _glfw.win32.dinput8.instance = LoadLibraryA("dinput8.dll");
    if (_glfw.win32.dinput8.instance)
    {
        _glfw.win32.dinput8.DirectInput8Create = (DIRECTINPUT8CREATE_T)
            GetProcAddress(_glfw.win32.dinput8.instance, "DirectInput8Create");
    }

    {
        int i;
        const char* names[] =
        {
            "xinput1_4.dll",
            "xinput1_3.dll",
            "xinput9_1_0.dll",
            "xinput1_2.dll",
            "xinput1_1.dll",
            NULL
        };

        for (i = 0;  names[i];  i++)
        {
            _glfw.win32.xinput.instance = LoadLibraryA(names[i]);
            if (_glfw.win32.xinput.instance)
            {
                _glfw.win32.xinput.XInputGetCapabilities = (XINPUTGETCAPABILITIES_T)
                    GetProcAddress(_glfw.win32.xinput.instance, "XInputGetCapabilities");
                _glfw.win32.xinput.XInputGetState = (XINPUTGETSTATE_T)
                    GetProcAddress(_glfw.win32.xinput.instance, "XInputGetState");

                break;
            }
        }
    }

    _glfw.win32.dwmapi.instance = LoadLibraryA("dwmapi.dll");
    if (_glfw.win32.dwmapi.instance)
    {
        _glfw.win32.dwmapi.DwmIsCompositionEnabled = (DWMISCOMPOSITIONENABLED_T)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmIsCompositionEnabled");
        _glfw.win32.dwmapi.DwmFlush = (DWMFLUSH_T)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmFlush");
    }

    _glfw.win32.shcore.instance = LoadLibraryA("shcore.dll");
    if (_glfw.win32.shcore.instance)
    {
        _glfw.win32.shcore.SetProcessDpiAwareness = (SETPROCESSDPIAWARENESS_T)
            GetProcAddress(_glfw.win32.shcore.instance, "SetProcessDpiAwareness");
    }

    return GLFW_TRUE;
}