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
struct drm_i915_gem_object {int madv; int /*<<< orphan*/  base; int /*<<< orphan*/ * pages; scalar_t__ pin_count; } ;
struct drm_i915_gem_madvise {int madv; int retained; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  I915_MADV_DONTNEED 129 
#define  I915_MADV_WILLNEED 128 
 int __I915_MADV_PURGED ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 scalar_t__ i915_gem_object_is_purgeable (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_truncate (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 

int
i915_gem_madvise_ioctl(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct drm_i915_gem_madvise *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	switch (args->madv) {
	case I915_MADV_DONTNEED:
	case I915_MADV_WILLNEED:
	    break;
	default:
	    return -EINVAL;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file_priv, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	if (obj->pin_count) {
		ret = -EINVAL;
		goto out;
	}

	if (obj->madv != __I915_MADV_PURGED)
		obj->madv = args->madv;

	/* if the object is no longer attached, discard its backing storage */
	if (i915_gem_object_is_purgeable(obj) && obj->pages == NULL)
		i915_gem_object_truncate(obj);

	args->retained = obj->madv != __I915_MADV_PURGED;

out:
	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}