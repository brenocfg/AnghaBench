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
typedef  scalar_t__ u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_3__ {scalar_t__* remap_info; } ;
struct TYPE_4__ {TYPE_1__ l3_parity; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ GEN7_DOP_CLOCK_GATE_ENABLE ; 
 scalar_t__ GEN7_L3LOG_BASE ; 
 int GEN7_L3LOG_SIZE ; 
 scalar_t__ GEN7_MISCCPCTL ; 
 int /*<<< orphan*/  HAS_L3_GPU_CACHE (struct drm_device*) ; 
 scalar_t__ I915_READ (scalar_t__) ; 
 int /*<<< orphan*/  I915_WRITE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  POSTING_READ (scalar_t__) ; 

void i915_gem_l3_remap(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 misccpctl;
	int i;

	if (!HAS_L3_GPU_CACHE(dev))
		return;

	if (!dev_priv->l3_parity.remap_info)
		return;

	misccpctl = I915_READ(GEN7_MISCCPCTL);
	I915_WRITE(GEN7_MISCCPCTL, misccpctl & ~GEN7_DOP_CLOCK_GATE_ENABLE);
	POSTING_READ(GEN7_MISCCPCTL);

	for (i = 0; i < GEN7_L3LOG_SIZE; i += 4) {
		u32 remap = I915_READ(GEN7_L3LOG_BASE + i);
		if (remap && remap != dev_priv->l3_parity.remap_info[i/4])
			DRM_DEBUG("0x%x was already programmed to %x\n",
				  GEN7_L3LOG_BASE + i, remap);
		if (remap && !dev_priv->l3_parity.remap_info[i/4])
			DRM_DEBUG_DRIVER("Clearing remapped register\n");
		I915_WRITE(GEN7_L3LOG_BASE + i, dev_priv->l3_parity.remap_info[i/4]);
	}

	/* Make sure all the writes land before disabling dop clock gating */
	POSTING_READ(GEN7_L3LOG_BASE);

	I915_WRITE(GEN7_MISCCPCTL, misccpctl);
}