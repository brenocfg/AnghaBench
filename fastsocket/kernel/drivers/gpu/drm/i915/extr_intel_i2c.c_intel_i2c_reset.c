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
struct drm_i915_private {scalar_t__ gpio_mmio_base; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ GMBUS0 ; 
 scalar_t__ GMBUS4 ; 
 int /*<<< orphan*/  I915_WRITE (scalar_t__,int /*<<< orphan*/ ) ; 

void
intel_i2c_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	I915_WRITE(dev_priv->gpio_mmio_base + GMBUS0, 0);
	I915_WRITE(dev_priv->gpio_mmio_base + GMBUS4, 0);
}