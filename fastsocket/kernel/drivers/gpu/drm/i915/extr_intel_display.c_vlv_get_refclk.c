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
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_ANALOG ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 scalar_t__ intel_panel_use_ssc (struct drm_i915_private*) ; 
 scalar_t__ intel_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlv_get_refclk(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	int refclk = 27000; /* for DP & HDMI */

	return 100000; /* only one validated so far */

	if (intel_pipe_has_type(crtc, INTEL_OUTPUT_ANALOG)) {
		refclk = 96000;
	} else if (intel_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) {
		if (intel_panel_use_ssc(dev_priv))
			refclk = 100000;
		else
			refclk = 96000;
	} else if (intel_pipe_has_type(crtc, INTEL_OUTPUT_EDP)) {
		refclk = 100000;
	}

	return refclk;
}