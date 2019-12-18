#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_lvds_encoder {int /*<<< orphan*/  reg; TYPE_2__ base; } ;
struct drm_i915_private {unsigned int bios_lvds_val; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 unsigned int I915_READ (int /*<<< orphan*/ ) ; 
 unsigned int LVDS_CLKB_POWER_MASK ; 
 unsigned int LVDS_CLKB_POWER_UP ; 
 unsigned int LVDS_DETECTED ; 
 unsigned int LVDS_PIPE_MASK ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int i915_lvds_channel_mode ; 
 int /*<<< orphan*/  intel_dual_link_lvds ; 

__attribute__((used)) static bool compute_is_dual_link_lvds(struct intel_lvds_encoder *lvds_encoder)
{
	struct drm_device *dev = lvds_encoder->base.base.dev;
	unsigned int val;
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* use the module option value if specified */
	if (i915_lvds_channel_mode > 0)
		return i915_lvds_channel_mode == 2;

	if (dmi_check_system(intel_dual_link_lvds))
		return true;

	/* BIOS should set the proper LVDS register value at boot, but
	 * in reality, it doesn't set the value when the lid is closed;
	 * we need to check "the value to be set" in VBT when LVDS
	 * register is uninitialized.
	 */
	val = I915_READ(lvds_encoder->reg);
	if (!(val & ~(LVDS_PIPE_MASK | LVDS_DETECTED)))
		val = dev_priv->bios_lvds_val;

	return (val & LVDS_CLKB_POWER_MASK) == LVDS_CLKB_POWER_UP;
}