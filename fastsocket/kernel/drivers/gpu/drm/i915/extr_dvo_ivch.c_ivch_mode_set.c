#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
struct intel_dvo_device {int dummy; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  VR01 ; 
 int VR01_PANEL_FIT_ENABLE ; 
 int /*<<< orphan*/  VR40 ; 
 int VR40_AUTO_RATIO_ENABLE ; 
 int VR40_CLOCK_GATING_ENABLE ; 
 int VR40_HORIZONTAL_INTERP_ENABLE ; 
 int VR40_STALL_ENABLE ; 
 int VR40_VERTICAL_INTERP_ENABLE ; 
 int /*<<< orphan*/  VR41 ; 
 int /*<<< orphan*/  VR42 ; 
 int /*<<< orphan*/  ivch_dump_regs (struct intel_dvo_device*) ; 
 int /*<<< orphan*/  ivch_write (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ivch_mode_set(struct intel_dvo_device *dvo,
			  struct drm_display_mode *mode,
			  struct drm_display_mode *adjusted_mode)
{
	uint16_t vr40 = 0;
	uint16_t vr01;

	vr01 = 0;
	vr40 = (VR40_STALL_ENABLE | VR40_VERTICAL_INTERP_ENABLE |
		VR40_HORIZONTAL_INTERP_ENABLE);

	if (mode->hdisplay != adjusted_mode->hdisplay ||
	    mode->vdisplay != adjusted_mode->vdisplay) {
		uint16_t x_ratio, y_ratio;

		vr01 |= VR01_PANEL_FIT_ENABLE;
		vr40 |= VR40_CLOCK_GATING_ENABLE;
		x_ratio = (((mode->hdisplay - 1) << 16) /
			   (adjusted_mode->hdisplay - 1)) >> 2;
		y_ratio = (((mode->vdisplay - 1) << 16) /
			   (adjusted_mode->vdisplay - 1)) >> 2;
		ivch_write(dvo, VR42, x_ratio);
		ivch_write(dvo, VR41, y_ratio);
	} else {
		vr01 &= ~VR01_PANEL_FIT_ENABLE;
		vr40 &= ~VR40_CLOCK_GATING_ENABLE;
	}
	vr40 &= ~VR40_AUTO_RATIO_ENABLE;

	ivch_write(dvo, VR01, vr01);
	ivch_write(dvo, VR40, vr40);

	ivch_dump_regs(dvo);
}