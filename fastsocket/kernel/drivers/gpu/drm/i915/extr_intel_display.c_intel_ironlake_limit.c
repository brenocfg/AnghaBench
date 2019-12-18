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
 int /*<<< orphan*/  INTEL_OUTPUT_DISPLAYPORT ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 scalar_t__ intel_is_dual_link_lvds (struct drm_device*) ; 
 int /*<<< orphan*/  intel_limits_ironlake_dac ; 
 int /*<<< orphan*/  intel_limits_ironlake_display_port ; 
 int /*<<< orphan*/  intel_limits_ironlake_dual_lvds ; 
 int /*<<< orphan*/  intel_limits_ironlake_dual_lvds_100m ; 
 int /*<<< orphan*/  intel_limits_ironlake_single_lvds ; 
 int /*<<< orphan*/  intel_limits_ironlake_single_lvds_100m ; 
 scalar_t__ intel_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const intel_limit_t *intel_ironlake_limit(struct drm_crtc *crtc,
						int refclk)
{
	struct drm_device *dev = crtc->dev;
	const intel_limit_t *limit;

	if (intel_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) {
		if (intel_is_dual_link_lvds(dev)) {
			/* LVDS dual channel */
			if (refclk == 100000)
				limit = &intel_limits_ironlake_dual_lvds_100m;
			else
				limit = &intel_limits_ironlake_dual_lvds;
		} else {
			if (refclk == 100000)
				limit = &intel_limits_ironlake_single_lvds_100m;
			else
				limit = &intel_limits_ironlake_single_lvds;
		}
	} else if (intel_pipe_has_type(crtc, INTEL_OUTPUT_DISPLAYPORT) ||
		   intel_pipe_has_type(crtc, INTEL_OUTPUT_EDP))
		limit = &intel_limits_ironlake_display_port;
	else
		limit = &intel_limits_ironlake_dac;

	return limit;
}