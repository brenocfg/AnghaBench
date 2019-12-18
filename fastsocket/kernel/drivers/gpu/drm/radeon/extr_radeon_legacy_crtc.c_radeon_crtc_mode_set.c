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
struct radeon_crtc {scalar_t__ crtc_id; scalar_t__ rmx_type; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ RMX_OFF ; 
 int /*<<< orphan*/  radeon_crtc_set_base (struct drm_crtc*,int,int,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  radeon_legacy_rmx_mode_set (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_overscan_setup (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_set_crtc_timing (struct drm_crtc*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  radeon_set_pll (struct drm_crtc*,struct drm_display_mode*) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int radeon_crtc_mode_set(struct drm_crtc *crtc,
				 struct drm_display_mode *mode,
				 struct drm_display_mode *adjusted_mode,
				 int x, int y, struct drm_framebuffer *old_fb)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	/* TODO TV */
	radeon_crtc_set_base(crtc, x, y, old_fb);
	radeon_set_crtc_timing(crtc, adjusted_mode);
	radeon_set_pll(crtc, adjusted_mode);
	radeon_overscan_setup(crtc, adjusted_mode);
	if (radeon_crtc->crtc_id == 0) {
		radeon_legacy_rmx_mode_set(crtc, adjusted_mode);
	} else {
		if (radeon_crtc->rmx_type != RMX_OFF) {
			/* FIXME: only first crtc has rmx what should we
			 * do ?
			 */
			DRM_ERROR("Mode need scaling but only first crtc can do that.\n");
		}
	}
	return 0;
}