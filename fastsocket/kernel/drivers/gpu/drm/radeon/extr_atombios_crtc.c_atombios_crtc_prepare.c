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
struct radeon_crtc {int in_mode_set; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  atombios_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_lock_crtc (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_powergate_crtc (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void atombios_crtc_prepare(struct drm_crtc *crtc)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;

	radeon_crtc->in_mode_set = true;

	/* disable crtc pair power gating before programming */
	if (ASIC_IS_DCE6(rdev))
		atombios_powergate_crtc(crtc, ATOM_DISABLE);

	atombios_lock_crtc(crtc, ATOM_ENABLE);
	atombios_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
}