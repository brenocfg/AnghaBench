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
struct intel_gmbus {int /*<<< orphan*/  adapter; } ;
struct drm_i915_private {struct intel_gmbus* gmbus; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int GMBUS_NUM_PORTS ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void intel_teardown_gmbus(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	for (i = 0; i < GMBUS_NUM_PORTS; i++) {
		struct intel_gmbus *bus = &dev_priv->gmbus[i];
		i2c_del_adapter(&bus->adapter);
	}
}