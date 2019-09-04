#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_16__ {TYPE_1__ x11; } ;
typedef  TYPE_4__ _GLFWmonitor ;
struct TYPE_17__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_5__ XRRCrtcGamma ;
struct TYPE_14__ {int /*<<< orphan*/  gammaBroken; scalar_t__ available; } ;
struct TYPE_15__ {int /*<<< orphan*/  display; TYPE_2__ randr; } ;
struct TYPE_19__ {TYPE_3__ x11; } ;
struct TYPE_18__ {int size; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_6__ GLFWgammaramp ;

/* Variables and functions */
 TYPE_5__* XRRAllocGamma (int) ; 
 int /*<<< orphan*/  XRRFreeGamma (TYPE_5__*) ; 
 int /*<<< orphan*/  XRRSetCrtcGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

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