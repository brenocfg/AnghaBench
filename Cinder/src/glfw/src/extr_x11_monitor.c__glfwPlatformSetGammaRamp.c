#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_19__ {TYPE_2__ x11; } ;
typedef  TYPE_5__ _GLFWmonitor ;
struct TYPE_20__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_6__ XRRCrtcGamma ;
struct TYPE_21__ {int size; scalar_t__ blue; scalar_t__ green; scalar_t__ red; } ;
struct TYPE_17__ {scalar_t__ available; } ;
struct TYPE_15__ {int /*<<< orphan*/  gammaBroken; scalar_t__ available; } ;
struct TYPE_18__ {int /*<<< orphan*/  screen; int /*<<< orphan*/  display; TYPE_3__ vidmode; TYPE_1__ randr; } ;
struct TYPE_14__ {TYPE_4__ x11; } ;
typedef  TYPE_7__ GLFWgammaramp ;

/* Variables and functions */
 int /*<<< orphan*/  XF86VidModeSetGammaRamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short*,unsigned short*,unsigned short*) ; 
 TYPE_6__* XRRAllocGamma (int) ; 
 int /*<<< orphan*/  XRRFreeGamma (TYPE_6__*) ; 
 int /*<<< orphan*/  XRRSetCrtcGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_10__ _glfw ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 

void _glfwPlatformSetGammaRamp(_GLFWmonitor* monitor, const GLFWgammaramp* ramp)
{
    if (_glfw.x11.randr.available && !_glfw.x11.randr.gammaBroken)
    {
        XRRCrtcGamma* gamma = XRRAllocGamma(ramp->size);

        memcpy(gamma->red, ramp->red, ramp->size * sizeof(unsigned short));
        memcpy(gamma->green, ramp->green, ramp->size * sizeof(unsigned short));
        memcpy(gamma->blue, ramp->blue, ramp->size * sizeof(unsigned short));

        XRRSetCrtcGamma(_glfw.x11.display, monitor->x11.crtc, gamma);
        XRRFreeGamma(gamma);
    }
#if defined(_GLFW_HAS_XF86VM)
    else if (_glfw.x11.vidmode.available)
    {
        XF86VidModeSetGammaRamp(_glfw.x11.display,
                                _glfw.x11.screen,
                                ramp->size,
                                (unsigned short*) ramp->red,
                                (unsigned short*) ramp->green,
                                (unsigned short*) ramp->blue);
    }
#endif /*_GLFW_HAS_XF86VM*/
}