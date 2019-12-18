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
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLC_PWM_CTL ; 
 int /*<<< orphan*/  BLC_PWM_CTL2 ; 
 int BLM_COMBINATION_MODE ; 
 int BLM_LEGACY_MODE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 

__attribute__((used)) static int is_backlight_combination_mode(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (INTEL_INFO(dev)->gen >= 4)
		return I915_READ(BLC_PWM_CTL2) & BLM_COMBINATION_MODE;

	if (IS_GEN2(dev))
		return I915_READ(BLC_PWM_CTL) & BLM_LEGACY_MODE;

	return 0;
}