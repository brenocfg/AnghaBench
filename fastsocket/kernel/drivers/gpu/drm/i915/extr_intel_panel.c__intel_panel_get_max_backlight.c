#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int i915_read_blc_pwm_ctl (struct drm_device*) ; 
 scalar_t__ is_backlight_combination_mode (struct drm_device*) ; 

__attribute__((used)) static u32 _intel_panel_get_max_backlight(struct drm_device *dev)
{
	u32 max;

	max = i915_read_blc_pwm_ctl(dev);

	if (HAS_PCH_SPLIT(dev)) {
		max >>= 16;
	} else {
		if (INTEL_INFO(dev)->gen < 4)
			max >>= 17;
		else
			max >>= 16;

		if (is_backlight_combination_mode(dev))
			max *= 0xff;
	}

	return max;
}