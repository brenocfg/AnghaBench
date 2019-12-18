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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
struct TYPE_5__ {scalar_t__ mappable_end; } ;
struct drm_i915_private {TYPE_1__ gtt; } ;
struct TYPE_6__ {scalar_t__ key; } ;
struct TYPE_7__ {TYPE_2__ hash; } ;
struct TYPE_8__ {scalar_t__ size; TYPE_3__ map_list; } ;
struct drm_i915_gem_object {scalar_t__ madv; TYPE_4__ base; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ I915_MADV_WILLNEED ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (TYPE_4__*) ; 
 int i915_gem_object_create_mmap_offset (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 

int
i915_gem_mmap_gtt(struct drm_file *file,
		  struct drm_device *dev,
		  uint32_t handle,
		  uint64_t *offset)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	if (obj->base.size > dev_priv->gtt.mappable_end) {
		ret = -E2BIG;
		goto out;
	}

	if (obj->madv != I915_MADV_WILLNEED) {
		DRM_ERROR("Attempting to mmap a purgeable buffer\n");
		ret = -EINVAL;
		goto out;
	}

	ret = i915_gem_object_create_mmap_offset(obj);
	if (ret)
		goto out;

	*offset = (u64)obj->base.map_list.hash.key << PAGE_SHIFT;

out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}