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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  i915_disable_vga (struct drm_device*) ; 
 int /*<<< orphan*/  i915_vgacntrl_reg (struct drm_device*) ; 

void i915_redisable_vga(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 vga_reg = i915_vgacntrl_reg(dev);

	if (I915_READ(vga_reg) != VGA_DISP_DISABLE) {
		DRM_DEBUG_KMS("Something enabled VGA plane, disabling it\n");
		i915_disable_vga(dev);
	}
}