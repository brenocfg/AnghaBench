#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dev; } ;
struct drm_i915_gem_object {int map_and_fenceable; scalar_t__ gtt_offset; int /*<<< orphan*/ * gtt_space; int /*<<< orphan*/  gtt_list; int /*<<< orphan*/  mm_list; scalar_t__ has_aliasing_ppgtt_mapping; scalar_t__ has_global_gtt_mapping; int /*<<< orphan*/ * pages; scalar_t__ pin_count; TYPE_2__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  unbound_list; int /*<<< orphan*/  aliasing_ppgtt; } ;
struct TYPE_8__ {TYPE_3__ mm; } ;
typedef  TYPE_4__ drm_i915_private_t ;
struct TYPE_5__ {TYPE_4__* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  drm_mm_put_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_gtt_finish_object (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_gtt_unbind_object (struct drm_i915_gem_object*) ; 
 int i915_gem_object_finish_gpu (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_finish_gtt (struct drm_i915_gem_object*) ; 
 int i915_gem_object_put_fence (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_ppgtt_unbind_object (int /*<<< orphan*/ ,struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_i915_gem_object_unbind (struct drm_i915_gem_object*) ; 

int
i915_gem_object_unbind(struct drm_i915_gem_object *obj)
{
	drm_i915_private_t *dev_priv = obj->base.dev->dev_private;
	int ret;

	if (obj->gtt_space == NULL)
		return 0;

	if (obj->pin_count)
		return -EBUSY;

	BUG_ON(obj->pages == NULL);

	ret = i915_gem_object_finish_gpu(obj);
	if (ret)
		return ret;
	/* Continue on if we fail due to EIO, the GPU is hung so we
	 * should be safe and we need to cleanup or else we might
	 * cause memory corruption through use-after-free.
	 */

	i915_gem_object_finish_gtt(obj);

	/* release the fence reg _after_ flushing */
	ret = i915_gem_object_put_fence(obj);
	if (ret)
		return ret;

	trace_i915_gem_object_unbind(obj);

	if (obj->has_global_gtt_mapping)
		i915_gem_gtt_unbind_object(obj);
	if (obj->has_aliasing_ppgtt_mapping) {
		i915_ppgtt_unbind_object(dev_priv->mm.aliasing_ppgtt, obj);
		obj->has_aliasing_ppgtt_mapping = 0;
	}
	i915_gem_gtt_finish_object(obj);

	list_del(&obj->mm_list);
	list_move_tail(&obj->gtt_list, &dev_priv->mm.unbound_list);
	/* Avoid an unnecessary call to unbind on rebind. */
	obj->map_and_fenceable = true;

	drm_mm_put_block(obj->gtt_space);
	obj->gtt_space = NULL;
	obj->gtt_offset = 0;

	return 0;
}