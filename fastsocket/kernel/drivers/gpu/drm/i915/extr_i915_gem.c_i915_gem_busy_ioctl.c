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
struct drm_i915_gem_object {int active; int /*<<< orphan*/  base; scalar_t__ ring; } ;
struct drm_i915_gem_busy {int busy; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOENT ; 
 int I915_NUM_RINGS ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 int i915_gem_object_flush_active (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int intel_ring_flag (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 

int
i915_gem_busy_ioctl(struct drm_device *dev, void *data,
		    struct drm_file *file)
{
	struct drm_i915_gem_busy *args = data;
	struct drm_i915_gem_object *obj;
	int ret;

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->handle));
	if (&obj->base == NULL) {
		ret = -ENOENT;
		goto unlock;
	}

	/* Count all active objects as busy, even if they are currently not used
	 * by the gpu. Users of this interface expect objects to eventually
	 * become non-busy without any further actions, therefore emit any
	 * necessary flushes here.
	 */
	ret = i915_gem_object_flush_active(obj);

	args->busy = obj->active;
	if (obj->ring) {
		BUILD_BUG_ON(I915_NUM_RINGS > 16);
		args->busy |= intel_ring_flag(obj->ring) << 16;
	}

	drm_gem_object_unreference(&obj->base);
unlock:
	mutex_unlock(&dev->struct_mutex);
	return ret;
}