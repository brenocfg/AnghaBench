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
typedef  void* u32 ;
struct intel_ring_buffer {int /*<<< orphan*/  active_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  fence_list; int /*<<< orphan*/  active_list; } ;
struct drm_i915_private {TYPE_1__ mm; struct drm_i915_fence_reg* fence_regs; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct drm_i915_gem_object {int active; size_t fence_reg; void* last_fenced_seqno; scalar_t__ fenced_gpu_access; void* last_read_seqno; int /*<<< orphan*/  ring_list; int /*<<< orphan*/  mm_list; TYPE_2__ base; struct intel_ring_buffer* ring; } ;
struct drm_i915_fence_reg {int /*<<< orphan*/  lru_list; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 size_t I915_FENCE_REG_NONE ; 
 int /*<<< orphan*/  drm_gem_object_reference (TYPE_2__*) ; 
 void* intel_ring_get_seqno (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
i915_gem_object_move_to_active(struct drm_i915_gem_object *obj,
			       struct intel_ring_buffer *ring)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 seqno = intel_ring_get_seqno(ring);

	BUG_ON(ring == NULL);
	obj->ring = ring;

	/* Add a reference if we're newly entering the active list. */
	if (!obj->active) {
		drm_gem_object_reference(&obj->base);
		obj->active = 1;
	}

	/* Move from whatever list we were on to the tail of execution. */
	list_move_tail(&obj->mm_list, &dev_priv->mm.active_list);
	list_move_tail(&obj->ring_list, &ring->active_list);

	obj->last_read_seqno = seqno;

	if (obj->fenced_gpu_access) {
		obj->last_fenced_seqno = seqno;

		/* Bump MRU to take account of the delayed flush */
		if (obj->fence_reg != I915_FENCE_REG_NONE) {
			struct drm_i915_fence_reg *reg;

			reg = &dev_priv->fence_regs[obj->fence_reg];
			list_move_tail(&reg->lru_list,
				       &dev_priv->mm.fence_list);
		}
	}
}