#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_i915_gem_set_tiling {scalar_t__ stride; scalar_t__ tiling_mode; scalar_t__ swizzle_mode; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {scalar_t__ size; } ;
struct drm_i915_gem_object {scalar_t__ tiling_mode; scalar_t__ stride; int map_and_fenceable; scalar_t__ gtt_offset; int fence_dirty; scalar_t__ fence_reg; TYPE_4__ base; int /*<<< orphan*/ * bit_17; scalar_t__ fenced_gpu_access; int /*<<< orphan*/ * gtt_space; scalar_t__ pin_count; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_3__* dev_private; } ;
struct TYPE_7__ {scalar_t__ mappable_end; } ;
struct TYPE_6__ {scalar_t__ bit_6_swizzle_x; scalar_t__ bit_6_swizzle_y; } ;
struct TYPE_8__ {TYPE_2__ gtt; TYPE_1__ mm; } ;
typedef  TYPE_3__ drm_i915_private_t ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9_10 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9_10_17 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9_17 ; 
 void* I915_BIT_6_SWIZZLE_NONE ; 
 scalar_t__ I915_BIT_6_SWIZZLE_UNKNOWN ; 
 scalar_t__ I915_FENCE_REG_NONE ; 
 scalar_t__ I915_TILING_NONE ; 
 scalar_t__ I915_TILING_X ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (TYPE_4__*) ; 
 int i915_gem_get_gtt_alignment (struct drm_device*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ i915_gem_object_fence_ok (struct drm_i915_gem_object*,scalar_t__) ; 
 scalar_t__ i915_gem_object_needs_bit17_swizzle (struct drm_i915_gem_object*) ; 
 int i915_gem_object_unbind (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_release_mmap (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_tiling_ok (struct drm_device*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 

int
i915_gem_set_tiling(struct drm_device *dev, void *data,
		   struct drm_file *file)
{
	struct drm_i915_gem_set_tiling *args = data;
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	int ret = 0;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL)
		return -ENOENT;

	if (!i915_tiling_ok(dev,
			    args->stride, obj->base.size, args->tiling_mode)) {
		drm_gem_object_unreference_unlocked(&obj->base);
		return -EINVAL;
	}

	if (obj->pin_count) {
		drm_gem_object_unreference_unlocked(&obj->base);
		return -EBUSY;
	}

	if (args->tiling_mode == I915_TILING_NONE) {
		args->swizzle_mode = I915_BIT_6_SWIZZLE_NONE;
		args->stride = 0;
	} else {
		if (args->tiling_mode == I915_TILING_X)
			args->swizzle_mode = dev_priv->mm.bit_6_swizzle_x;
		else
			args->swizzle_mode = dev_priv->mm.bit_6_swizzle_y;

		/* Hide bit 17 swizzling from the user.  This prevents old Mesa
		 * from aborting the application on sw fallbacks to bit 17,
		 * and we use the pread/pwrite bit17 paths to swizzle for it.
		 * If there was a user that was relying on the swizzle
		 * information for drm_intel_bo_map()ed reads/writes this would
		 * break it, but we don't have any of those.
		 */
		if (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_17)
			args->swizzle_mode = I915_BIT_6_SWIZZLE_9;
		if (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_10_17)
			args->swizzle_mode = I915_BIT_6_SWIZZLE_9_10;

		/* If we can't handle the swizzling, make it untiled. */
		if (args->swizzle_mode == I915_BIT_6_SWIZZLE_UNKNOWN) {
			args->tiling_mode = I915_TILING_NONE;
			args->swizzle_mode = I915_BIT_6_SWIZZLE_NONE;
			args->stride = 0;
		}
	}

	mutex_lock(&dev->struct_mutex);
	if (args->tiling_mode != obj->tiling_mode ||
	    args->stride != obj->stride) {
		/* We need to rebind the object if its current allocation
		 * no longer meets the alignment restrictions for its new
		 * tiling mode. Otherwise we can just leave it alone, but
		 * need to ensure that any fence register is updated before
		 * the next fenced (either through the GTT or by the BLT unit
		 * on older GPUs) access.
		 *
		 * After updating the tiling parameters, we then flag whether
		 * we need to update an associated fence register. Note this
		 * has to also include the unfenced register the GPU uses
		 * whilst executing a fenced command for an untiled object.
		 */

		obj->map_and_fenceable =
			obj->gtt_space == NULL ||
			(obj->gtt_offset + obj->base.size <= dev_priv->gtt.mappable_end &&
			 i915_gem_object_fence_ok(obj, args->tiling_mode));

		/* Rebind if we need a change of alignment */
		if (!obj->map_and_fenceable) {
			u32 unfenced_alignment =
				i915_gem_get_gtt_alignment(dev, obj->base.size,
							    args->tiling_mode,
							    false);
			if (obj->gtt_offset & (unfenced_alignment - 1))
				ret = i915_gem_object_unbind(obj);
		}

		if (ret == 0) {
			obj->fence_dirty =
				obj->fenced_gpu_access ||
				obj->fence_reg != I915_FENCE_REG_NONE;

			obj->tiling_mode = args->tiling_mode;
			obj->stride = args->stride;

			/* Force the fence to be reacquired for GTT access */
			i915_gem_release_mmap(obj);
		}
	}
	/* we have to maintain this existing ABI... */
	args->stride = obj->stride;
	args->tiling_mode = obj->tiling_mode;

	/* Try to preallocate memory required to save swizzling on put-pages */
	if (i915_gem_object_needs_bit17_swizzle(obj)) {
		if (obj->bit_17 == NULL) {
			obj->bit_17 = kmalloc(BITS_TO_LONGS(obj->base.size >> PAGE_SHIFT) *
					      sizeof(long), GFP_KERNEL);
		}
	} else {
		kfree(obj->bit_17);
		obj->bit_17 = NULL;
	}

	drm_gem_object_unreference(&obj->base);
	mutex_unlock(&dev->struct_mutex);

	return ret;
}