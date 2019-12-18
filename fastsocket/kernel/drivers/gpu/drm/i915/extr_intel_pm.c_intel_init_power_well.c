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

/* Variables and functions */
 int /*<<< orphan*/  HSW_PWR_WELL_BIOS ; 
 int HSW_PWR_WELL_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  intel_set_power_well (struct drm_device*,int) ; 

void intel_init_power_well(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!IS_HASWELL(dev))
		return;

	/* For now, we need the power well to be always enabled. */
	intel_set_power_well(dev, true);

	/* We're taking over the BIOS, so clear any requests made by it since
	 * the driver is in charge now. */
	if (I915_READ(HSW_PWR_WELL_BIOS) & HSW_PWR_WELL_ENABLE)
		I915_WRITE(HSW_PWR_WELL_BIOS, 0);
}