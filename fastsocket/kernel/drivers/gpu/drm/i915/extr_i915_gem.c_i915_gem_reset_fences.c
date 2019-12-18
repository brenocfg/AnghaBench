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
struct TYPE_2__ {int /*<<< orphan*/  fence_list; } ;
struct drm_i915_private {int num_fence_regs; TYPE_1__ mm; struct drm_i915_fence_reg* fence_regs; } ;
struct drm_i915_fence_reg {int /*<<< orphan*/  lru_list; int /*<<< orphan*/ * obj; scalar_t__ pin_count; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_fence_lost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_write_fence (struct drm_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_gem_reset_fences(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	for (i = 0; i < dev_priv->num_fence_regs; i++) {
		struct drm_i915_fence_reg *reg = &dev_priv->fence_regs[i];

		i915_gem_write_fence(dev, i, NULL);

		if (reg->obj)
			i915_gem_object_fence_lost(reg->obj);

		reg->pin_count = 0;
		reg->obj = NULL;
		INIT_LIST_HEAD(&reg->lru_list);
	}

	INIT_LIST_HEAD(&dev_priv->mm.fence_list);
}