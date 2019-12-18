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
typedef  int u32 ;
struct intel_gmbus {int /*<<< orphan*/  gpio_reg; struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int GPIO_CLOCK_PULLUP_DISABLE ; 
 int GPIO_DATA_PULLUP_DISABLE ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_845G (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_device*) ; 

__attribute__((used)) static u32 get_reserved(struct intel_gmbus *bus)
{
	struct drm_i915_private *dev_priv = bus->dev_priv;
	struct drm_device *dev = dev_priv->dev;
	u32 reserved = 0;

	/* On most chips, these bits must be preserved in software. */
	if (!IS_I830(dev) && !IS_845G(dev))
		reserved = I915_READ_NOTRACE(bus->gpio_reg) &
					     (GPIO_DATA_PULLUP_DISABLE |
					      GPIO_CLOCK_PULLUP_DISABLE);

	return reserved;
}