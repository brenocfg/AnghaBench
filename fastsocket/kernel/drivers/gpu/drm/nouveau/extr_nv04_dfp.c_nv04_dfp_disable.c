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
struct nv04_crtc_reg {int /*<<< orphan*/ * CRTC; int /*<<< orphan*/  fp_control; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct nv04_crtc_reg* crtc_reg; } ;
struct TYPE_4__ {TYPE_1__ mode_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_TG_CONTROL_OFF ; 
 int FP_TG_CONTROL_ON ; 
 int NVReadRAMDAC (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_CIO_CRE_LCD_ROUTE_MASK ; 
 size_t NV_CIO_CRE_LCD__INDEX ; 
 int /*<<< orphan*/  NV_PRAMDAC_FP_TG_CONTROL ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* nv04_display (struct drm_device*) ; 

void nv04_dfp_disable(struct drm_device *dev, int head)
{
	struct nv04_crtc_reg *crtcstate = nv04_display(dev)->mode_reg.crtc_reg;

	if (NVReadRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL) &
	    FP_TG_CONTROL_ON) {
		/* digital remnants must be cleaned before new crtc
		 * values programmed.  delay is time for the vga stuff
		 * to realise it's in control again
		 */
		NVWriteRAMDAC(dev, head, NV_PRAMDAC_FP_TG_CONTROL,
			      FP_TG_CONTROL_OFF);
		msleep(50);
	}
	/* don't inadvertently turn it on when state written later */
	crtcstate[head].fp_control = FP_TG_CONTROL_OFF;
	crtcstate[head].CRTC[NV_CIO_CRE_LCD__INDEX] &=
		~NV_CIO_CRE_LCD_ROUTE_MASK;
}