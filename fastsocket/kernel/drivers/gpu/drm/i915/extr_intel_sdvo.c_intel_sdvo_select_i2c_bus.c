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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdvo_device_mapping {int /*<<< orphan*/  i2c_pin; scalar_t__ initialized; } ;
struct intel_sdvo {int /*<<< orphan*/  i2c; scalar_t__ is_sdvob; } ;
struct drm_i915_private {struct sdvo_device_mapping* sdvo_mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS_PORT_DPB ; 
 int /*<<< orphan*/  intel_gmbus_force_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_gmbus_is_port_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_sdvo_select_i2c_bus(struct drm_i915_private *dev_priv,
			  struct intel_sdvo *sdvo, u32 reg)
{
	struct sdvo_device_mapping *mapping;
	u8 pin;

	if (sdvo->is_sdvob)
		mapping = &dev_priv->sdvo_mappings[0];
	else
		mapping = &dev_priv->sdvo_mappings[1];

	if (mapping->initialized && intel_gmbus_is_port_valid(mapping->i2c_pin))
		pin = mapping->i2c_pin;
	else
		pin = GMBUS_PORT_DPB;

	sdvo->i2c = intel_gmbus_get_adapter(dev_priv, pin);

	/* With gmbus we should be able to drive sdvo i2c at 2MHz, but somehow
	 * our code totally fails once we start using gmbus. Hence fall back to
	 * bit banging for now. */
	intel_gmbus_force_bit(sdvo->i2c, true);
}