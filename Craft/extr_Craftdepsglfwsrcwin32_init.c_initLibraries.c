#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* instance; scalar_t__ DwmFlush; scalar_t__ DwmIsCompositionEnabled; } ;
struct TYPE_7__ {void* instance; scalar_t__ ChangeWindowMessageFilterEx; scalar_t__ SetProcessDPIAware; } ;
struct TYPE_6__ {scalar_t__ timeGetTime; scalar_t__ joyGetPosEx; scalar_t__ joyGetPos; scalar_t__ joyGetDevCaps; void* instance; } ;
struct TYPE_9__ {TYPE_3__ dwmapi; TYPE_2__ user32; TYPE_1__ winmm; } ;
struct TYPE_10__ {TYPE_4__ win32; } ;
typedef  scalar_t__ TIMEGETTIME_T ;
typedef  scalar_t__ SETPROCESSDPIAWARE_T ;
typedef  scalar_t__ JOYGETPOS_T ;
typedef  scalar_t__ JOYGETPOSEX_T ;
typedef  scalar_t__ JOYGETDEVCAPS_T ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  scalar_t__ DWMISCOMPOSITIONENABLED_T ;
typedef  scalar_t__ DWMFLUSH_T ;
typedef  scalar_t__ CHANGEWINDOWMESSAGEFILTEREX_T ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 scalar_t__ GetProcAddress (void*,char*) ; 
 void* LoadLibraryW (char*) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static GLboolean initLibraries(void)
{
    _glfw.win32.winmm.instance = LoadLibraryW(L"winmm.dll");
    if (!_glfw.win32.winmm.instance)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Failed to load winmm.dll");
        return GL_FALSE;
    }

    _glfw.win32.winmm.joyGetDevCaps = (JOYGETDEVCAPS_T)
        GetProcAddress(_glfw.win32.winmm.instance, "joyGetDevCapsW");
    _glfw.win32.winmm.joyGetPos = (JOYGETPOS_T)
        GetProcAddress(_glfw.win32.winmm.instance, "joyGetPos");
    _glfw.win32.winmm.joyGetPosEx = (JOYGETPOSEX_T)
        GetProcAddress(_glfw.win32.winmm.instance, "joyGetPosEx");
    _glfw.win32.winmm.timeGetTime = (TIMEGETTIME_T)
        GetProcAddress(_glfw.win32.winmm.instance, "timeGetTime");

    if (!_glfw.win32.winmm.joyGetDevCaps ||
        !_glfw.win32.winmm.joyGetPos ||
        !_glfw.win32.winmm.joyGetPosEx ||
        !_glfw.win32.winmm.timeGetTime)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Failed to load winmm functions");
        return GL_FALSE;
    }

    _glfw.win32.user32.instance = LoadLibraryW(L"user32.dll");
    if (_glfw.win32.user32.instance)
    {
        _glfw.win32.user32.SetProcessDPIAware = (SETPROCESSDPIAWARE_T)
            GetProcAddress(_glfw.win32.user32.instance, "SetProcessDPIAware");
        _glfw.win32.user32.ChangeWindowMessageFilterEx = (CHANGEWINDOWMESSAGEFILTEREX_T)
            GetProcAddress(_glfw.win32.user32.instance, "ChangeWindowMessageFilterEx");
    }

    _glfw.win32.dwmapi.instance = LoadLibraryW(L"dwmapi.dll");
    if (_glfw.win32.dwmapi.instance)
    {
        _glfw.win32.dwmapi.DwmIsCompositionEnabled = (DWMISCOMPOSITIONENABLED_T)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmIsCompositionEnabled");
        _glfw.win32.dwmapi.DwmFlush = (DWMFLUSH_T)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmFlush");
    }

    return GL_TRUE;
}