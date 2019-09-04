#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dm ;
struct TYPE_16__ {int /*<<< orphan*/  modeChanged; int /*<<< orphan*/  adapterName; } ;
struct TYPE_17__ {TYPE_1__ win32; } ;
typedef  TYPE_2__ _GLFWmonitor ;
struct TYPE_19__ {int dmSize; int dmFields; int dmBitsPerPel; int /*<<< orphan*/  dmDisplayFrequency; int /*<<< orphan*/  dmPelsHeight; int /*<<< orphan*/  dmPelsWidth; } ;
struct TYPE_18__ {int redBits; int greenBits; int blueBits; int /*<<< orphan*/  refreshRate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_3__ GLFWvidmode ;
typedef  TYPE_4__ DEVMODEW ;

/* Variables and functions */
 int /*<<< orphan*/  CDS_FULLSCREEN ; 
 scalar_t__ ChangeDisplaySettingsExW (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DISP_CHANGE_SUCCESSFUL ; 
 int DM_BITSPERPEL ; 
 int DM_DISPLAYFREQUENCY ; 
 int DM_PELSHEIGHT ; 
 int DM_PELSWIDTH ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 
 TYPE_3__* _glfwChooseVideoMode (TYPE_2__*,TYPE_3__ const*) ; 
 scalar_t__ _glfwCompareVideoModes (TYPE_3__*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwPlatformGetVideoMode (TYPE_2__*,TYPE_3__*) ; 

GLboolean _glfwSetVideoMode(_GLFWmonitor* monitor, const GLFWvidmode* desired)
{
    GLFWvidmode current;
    const GLFWvidmode* best;
    DEVMODEW dm;

    best = _glfwChooseVideoMode(monitor, desired);
    _glfwPlatformGetVideoMode(monitor, &current);
    if (_glfwCompareVideoModes(&current, best) == 0)
        return GL_TRUE;

    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(DEVMODEW);
    dm.dmFields           = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL |
                            DM_DISPLAYFREQUENCY;
    dm.dmPelsWidth        = best->width;
    dm.dmPelsHeight       = best->height;
    dm.dmBitsPerPel       = best->redBits + best->greenBits + best->blueBits;
    dm.dmDisplayFrequency = best->refreshRate;

    if (dm.dmBitsPerPel < 15 || dm.dmBitsPerPel >= 24)
        dm.dmBitsPerPel = 32;

    if (ChangeDisplaySettingsExW(monitor->win32.adapterName,
                                 &dm,
                                 NULL,
                                 CDS_FULLSCREEN,
                                 NULL) != DISP_CHANGE_SUCCESSFUL)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Win32: Failed to set video mode");
        return GL_FALSE;
    }

    monitor->win32.modeChanged = GL_TRUE;
    return GL_TRUE;
}