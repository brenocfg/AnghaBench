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
struct TYPE_3__ {int /*<<< orphan*/  fence_list; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct drm_i915_gem_object {int fence_reg; TYPE_2__ base; } ;
struct drm_i915_fence_reg {int /*<<< orphan*/  lru_list; struct drm_i915_gem_object* obj; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ HAS_LLC (struct drm_device*) ; 
 int I915_FENCE_REG_NONE ; 
 int fence_number (struct drm_i915_private*,struct drm_i915_fence_reg*) ; 
 int /*<<< orphan*/  i915_gem_write_fence (struct drm_device*,int,struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_write_fence__ipi ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void i915_gem_object_update_fence(struct drm_i915_gem_object *obj,
					 struct drm_i915_fence_reg *fence,
					 bool enable)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	int fence_reg = fence_number(dev_priv, fence);

	/* In order to fully serialize access to the fenced region and
	 * the update to the fence register we need to take extreme
	 * measures on SNB+. In theory, the write to the fence register
	 * flushes all memory transactions before, and coupled with the
	 * mb() placed around the register write we serialise all memory
	 * operations with respect to the changes in the tiler. Yet, on
	 * SNB+ we need to take a step further and emit an explicit wbinvd()
	 * on each processor in order to manually flush all memory
	 * transactions before updating the fence register.
	 */
	if (HAS_LLC(obj->base.dev))
		on_each_cpu(i915_gem_write_fence__ipi, NULL, 1);
	i915_gem_write_fence(dev, fence_reg, enable ? obj : NULL);

	if (enable) {
		obj->fence_reg = fence_reg;
		fence->obj = obj;
		list_move_tail(&fence->lru_list, &dev_priv->mm.fence_list);
	} else {
		obj->fence_reg = I915_FENCE_REG_NONE;
		fence->obj = NULL;
		list_del_init(&fence->lru_list);
	}
}