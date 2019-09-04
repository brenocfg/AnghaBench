#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_17__ {TYPE_2__ x11; } ;
typedef  TYPE_4__ _GLFWmonitor ;
struct TYPE_18__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_5__ XRRCrtcGamma ;
struct TYPE_19__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_16__ {int /*<<< orphan*/  gammaBroken; scalar_t__ available; } ;
struct TYPE_14__ {int /*<<< orphan*/  display; TYPE_3__ randr; } ;
struct TYPE_13__ {TYPE_1__ x11; } ;
typedef  TYPE_6__ GLFWgammaramp ;

/* Variables and functions */
 int /*<<< orphan*/  XRRFreeGamma (TYPE_5__*) ; 
 TYPE_5__* XRRGetCrtcGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t XRRGetCrtcGammaSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__ _glfw ; 
 int /*<<< orphan*/  _glfwAllocGammaArrays (TYPE_6__*,size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

void _glfwPlatformGetGammaRamp(_GLFWmonitor* monitor, GLFWgammaramp* ramp)
{
    if (_glfw.x11.randr.available && !_glfw.x11.randr.gammaBroken)
    {
        const size_t size = XRRGetCrtcGammaSize(_glfw.x11.display,
                                                monitor->x11.crtc);
        XRRCrtcGamma* gamma = XRRGetCrtcGamma(_glfw.x11.display,
                                              monitor->x11.crtc);

        _glfwAllocGammaArrays(ramp, size);

        memcpy(ramp->red, gamma->red, size * sizeof(unsigned short));
        memcpy(ramp->green, gamma->green, size * sizeof(unsigned short));
        memcpy(ramp->blue, gamma->blue, size * sizeof(unsigned short));

        XRRFreeGamma(gamma);
    }
#if defined(_GLFW_HAS_XF86VM)
    else if (_glfw.x11.vidmode.available)
    {
        int size;
        XF86VidModeGetGammaRampSize(_glfw.x11.display, _glfw.x11.screen, &size);

        _glfwAllocGammaArrays(ramp, size);

        XF86VidModeGetGammaRamp(_glfw.x11.display,
                                _glfw.x11.screen,
                                ramp->size, ramp->red, ramp->green, ramp->blue);
    }
#endif /*_GLFW_HAS_XF86VM*/
}