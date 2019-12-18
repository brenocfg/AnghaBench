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
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  intel_limit_t ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 scalar_t__ IS_G4X (struct drm_device*) ; 
 int /*<<< orphan*/  IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/ * intel_g4x_limit (struct drm_crtc*) ; 
 int /*<<< orphan*/ * intel_ironlake_limit (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  intel_limits_i8xx_dvo ; 
 int /*<<< orphan*/  intel_limits_i8xx_lvds ; 
 int /*<<< orphan*/  intel_limits_i9xx_lvds ; 
 int /*<<< orphan*/  intel_limits_i9xx_sdvo ; 
 int /*<<< orphan*/  intel_limits_pineview_lvds ; 
 int /*<<< orphan*/  intel_limits_pineview_sdvo ; 
 int /*<<< orphan*/  intel_limits_vlv_dac ; 
 int /*<<< orphan*/  intel_limits_vlv_dp ; 
 int /*<<< orphan*/  intel_limits_vlv_hdmi ; 
 scalar_t__ intel_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const intel_limit_t *intel_limit(struct drm_crtc *crtc, int refclk)
{
	struct drm_device *dev = crtc->dev;
	const intel_limit_t *limit;

	if (HAS_PCH_SPLIT(dev))
		limit = intel_ironlake_limit(crtc, refclk);
	else if (IS_G4X(dev)) {
		limit = intel_g4x_limit(crtc);
	} else if (IS_PINEVIEW(dev)) {
		if (intel_pipe_has_type(crtc, INTEL_OUTPUT_LVDS))
			limit = &intel_limits_pineview_lvds;
		else
			limit = &intel_limits_pineview_sdvo;
	} else if (IS_VALLEYVIEW(dev)) {
		if (intel_pipe_has_type(crtc, INTEL_OUTPUT_ANALOG))
			limit = &intel_limits_vlv_dac;
		else if (intel_pipe_has_type(crtc, INTEL_OUTPUT_HDMI))
			limit = &intel_limits_vlv_hdmi;
		else
			limit = &intel_limits_vlv_dp;
	} else if (!IS_GEN2(dev)) {
		if (intel_pipe_has_type(crtc, INTEL_OUTPUT_LVDS))
			limit = &intel_limits_i9xx_lvds;
		else
			limit = &intel_limits_i9xx_sdvo;
	} else {
		if (intel_pipe_has_type(crtc, INTEL_OUTPUT_LVDS))
			limit = &intel_limits_i8xx_lvds;
		else
			limit = &intel_limits_i8xx_dvo;
	}
	return limit;
}