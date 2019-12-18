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
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_DRIVER ; 
 int HSW_PWR_WELL_ENABLE ; 
 int HSW_PWR_WELL_STATE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  i915_disable_power_well ; 
 scalar_t__ wait_for (int,int) ; 

void intel_set_power_well(struct drm_device *dev, bool enable)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	bool is_enabled, enable_requested;
	uint32_t tmp;

	if (!IS_HASWELL(dev))
		return;

	if (!i915_disable_power_well && !enable)
		return;

	tmp = I915_READ(HSW_PWR_WELL_DRIVER);
	is_enabled = tmp & HSW_PWR_WELL_STATE;
	enable_requested = tmp & HSW_PWR_WELL_ENABLE;

	if (enable) {
		if (!enable_requested)
			I915_WRITE(HSW_PWR_WELL_DRIVER, HSW_PWR_WELL_ENABLE);

		if (!is_enabled) {
			DRM_DEBUG_KMS("Enabling power well\n");
			if (wait_for((I915_READ(HSW_PWR_WELL_DRIVER) &
				      HSW_PWR_WELL_STATE), 20))
				DRM_ERROR("Timeout enabling power well\n");
		}
	} else {
		if (enable_requested) {
			I915_WRITE(HSW_PWR_WELL_DRIVER, 0);
			DRM_DEBUG_KMS("Requesting to disable the power well\n");
		}
	}
}