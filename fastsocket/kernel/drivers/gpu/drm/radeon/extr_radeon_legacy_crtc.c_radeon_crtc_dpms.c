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
typedef  int uint32_t ;
struct radeon_device {int flags; } ;
struct radeon_crtc {int enabled; scalar_t__ crtc_id; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int RADEON_CRTC2_DISP_DIS ; 
 int RADEON_CRTC2_DISP_REQ_EN_B ; 
 int RADEON_CRTC2_EN ; 
 int /*<<< orphan*/  RADEON_CRTC2_GEN_CNTL ; 
 int RADEON_CRTC2_HSYNC_DIS ; 
 int RADEON_CRTC2_VSYNC_DIS ; 
 int RADEON_CRTC_CRT_ON ; 
 int RADEON_CRTC_DISPLAY_DIS ; 
 int RADEON_CRTC_DISP_REQ_EN_B ; 
 int RADEON_CRTC_EN ; 
 int /*<<< orphan*/  RADEON_CRTC_EXT_CNTL ; 
 int /*<<< orphan*/  RADEON_CRTC_GEN_CNTL ; 
 int RADEON_CRTC_HSYNC_DIS ; 
 int RADEON_CRTC_VSYNC_DIS ; 
 int RADEON_SINGLE_CRTC ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  drm_vblank_post_modeset (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  drm_vblank_pre_modeset (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void radeon_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t crtc_ext_cntl = 0;
	uint32_t mask;

	if (radeon_crtc->crtc_id)
		mask = (RADEON_CRTC2_DISP_DIS |
			RADEON_CRTC2_VSYNC_DIS |
			RADEON_CRTC2_HSYNC_DIS |
			RADEON_CRTC2_DISP_REQ_EN_B);
	else
		mask = (RADEON_CRTC_DISPLAY_DIS |
			RADEON_CRTC_VSYNC_DIS |
			RADEON_CRTC_HSYNC_DIS);

	/*
	 * On all dual CRTC GPUs this bit controls the CRTC of the primary DAC.
	 * Therefore it is set in the DAC DMPS function.
	 * This is different for GPU's with a single CRTC but a primary and a
	 * TV DAC: here it controls the single CRTC no matter where it is
	 * routed. Therefore we set it here.
	 */
	if (rdev->flags & RADEON_SINGLE_CRTC)
		crtc_ext_cntl = RADEON_CRTC_CRT_ON;
	
	switch (mode) {
	case DRM_MODE_DPMS_ON:
		radeon_crtc->enabled = true;
		/* adjust pm to dpms changes BEFORE enabling crtcs */
		radeon_pm_compute_clocks(rdev);
		if (radeon_crtc->crtc_id)
			WREG32_P(RADEON_CRTC2_GEN_CNTL, RADEON_CRTC2_EN, ~(RADEON_CRTC2_EN | mask));
		else {
			WREG32_P(RADEON_CRTC_GEN_CNTL, RADEON_CRTC_EN, ~(RADEON_CRTC_EN |
									 RADEON_CRTC_DISP_REQ_EN_B));
			WREG32_P(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl, ~(mask | crtc_ext_cntl));
		}
		drm_vblank_post_modeset(dev, radeon_crtc->crtc_id);
		radeon_crtc_load_lut(crtc);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		drm_vblank_pre_modeset(dev, radeon_crtc->crtc_id);
		if (radeon_crtc->crtc_id)
			WREG32_P(RADEON_CRTC2_GEN_CNTL, mask, ~(RADEON_CRTC2_EN | mask));
		else {
			WREG32_P(RADEON_CRTC_GEN_CNTL, RADEON_CRTC_DISP_REQ_EN_B, ~(RADEON_CRTC_EN |
										    RADEON_CRTC_DISP_REQ_EN_B));
			WREG32_P(RADEON_CRTC_EXT_CNTL, mask, ~(mask | crtc_ext_cntl));
		}
		radeon_crtc->enabled = false;
		/* adjust pm to dpms changes AFTER disabling crtcs */
		radeon_pm_compute_clocks(rdev);
		break;
	}
}