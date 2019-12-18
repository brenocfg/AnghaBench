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
struct radeon_device {int dummy; } ;
struct radeon_crtc {int enabled; int /*<<< orphan*/  crtc_id; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE3 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  atombios_blank_crtc (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_enable_crtc (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_enable_crtc_memreq (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vblank_post_modeset (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vblank_pre_modeset (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_crtc_load_lut (struct drm_crtc*) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

void atombios_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		radeon_crtc->enabled = true;
		/* adjust pm to dpms changes BEFORE enabling crtcs */
		radeon_pm_compute_clocks(rdev);
		atombios_enable_crtc(crtc, ATOM_ENABLE);
		if (ASIC_IS_DCE3(rdev) && !ASIC_IS_DCE6(rdev))
			atombios_enable_crtc_memreq(crtc, ATOM_ENABLE);
		atombios_blank_crtc(crtc, ATOM_DISABLE);
		drm_vblank_post_modeset(dev, radeon_crtc->crtc_id);
		radeon_crtc_load_lut(crtc);
		break;
	case DRM_MODE_DPMS_STANDBY:
	case DRM_MODE_DPMS_SUSPEND:
	case DRM_MODE_DPMS_OFF:
		drm_vblank_pre_modeset(dev, radeon_crtc->crtc_id);
		if (radeon_crtc->enabled)
			atombios_blank_crtc(crtc, ATOM_ENABLE);
		if (ASIC_IS_DCE3(rdev) && !ASIC_IS_DCE6(rdev))
			atombios_enable_crtc_memreq(crtc, ATOM_DISABLE);
		atombios_enable_crtc(crtc, ATOM_DISABLE);
		radeon_crtc->enabled = false;
		/* adjust pm to dpms changes AFTER disabling crtcs */
		radeon_pm_compute_clocks(rdev);
		break;
	}
}