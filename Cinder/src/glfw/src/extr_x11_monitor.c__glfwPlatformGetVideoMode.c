#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_18__ {TYPE_2__ x11; } ;
typedef  TYPE_4__ _GLFWmonitor ;
typedef  int /*<<< orphan*/  XRRScreenResources ;
struct TYPE_19__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_5__ XRRCrtcInfo ;
struct TYPE_20__ {int /*<<< orphan*/  blueBits; int /*<<< orphan*/  greenBits; int /*<<< orphan*/  redBits; scalar_t__ refreshRate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {int /*<<< orphan*/  monitorBroken; scalar_t__ available; } ;
struct TYPE_17__ {int /*<<< orphan*/  screen; int /*<<< orphan*/  display; int /*<<< orphan*/  root; TYPE_1__ randr; } ;
struct TYPE_14__ {TYPE_3__ x11; } ;
typedef  TYPE_6__ GLFWvidmode ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultDepth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisplayHeight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisplayWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRRFreeCrtcInfo (TYPE_5__*) ; 
 int /*<<< orphan*/  XRRFreeScreenResources (int /*<<< orphan*/ *) ; 
 TYPE_5__* XRRGetCrtcInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XRRGetScreenResourcesCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__ _glfw ; 
 int /*<<< orphan*/  _glfwSplitBPP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getModeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__ vidmodeFromModeInfo (int /*<<< orphan*/ ,TYPE_5__*) ; 

void _glfwPlatformGetVideoMode(_GLFWmonitor* monitor, GLFWvidmode* mode)
{
    if (_glfw.x11.randr.available && !_glfw.x11.randr.monitorBroken)
    {
        XRRScreenResources* sr;
        XRRCrtcInfo* ci;

        sr = XRRGetScreenResourcesCurrent(_glfw.x11.display, _glfw.x11.root);
        ci = XRRGetCrtcInfo(_glfw.x11.display, sr, monitor->x11.crtc);

        *mode = vidmodeFromModeInfo(getModeInfo(sr, ci->mode), ci);

        XRRFreeCrtcInfo(ci);
        XRRFreeScreenResources(sr);
    }
    else
    {
        mode->width = DisplayWidth(_glfw.x11.display, _glfw.x11.screen);
        mode->height = DisplayHeight(_glfw.x11.display, _glfw.x11.screen);
        mode->refreshRate = 0;

        _glfwSplitBPP(DefaultDepth(_glfw.x11.display, _glfw.x11.screen),
                      &mode->redBits, &mode->greenBits, &mode->blueBits);
    }
}