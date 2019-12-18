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
struct timespec {int dummy; } ;
struct intel_ring_buffer {int dummy; } ;
struct drm_i915_gem_wait {scalar_t__ timeout_ns; int /*<<< orphan*/  bo_handle; } ;
struct drm_i915_gem_object {scalar_t__ last_read_seqno; int /*<<< orphan*/  base; struct intel_ring_buffer* ring; scalar_t__ active; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  reset_counter; } ;
struct TYPE_4__ {TYPE_1__ gpu_error; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 int ENOENT ; 
 int ETIME ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __wait_seqno (struct intel_ring_buffer*,scalar_t__,unsigned int,int,struct timespec*) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 int i915_gem_object_flush_active (struct drm_i915_gem_object*) ; 
 int i915_mutex_lock_interruptible (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct timespec ns_to_timespec (scalar_t__) ; 
 scalar_t__ timespec_to_ns (struct timespec*) ; 
 int /*<<< orphan*/  timespec_valid (struct timespec*) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 

int
i915_gem_wait_ioctl(struct drm_device *dev, void *data, struct drm_file *file)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_gem_wait *args = data;
	struct drm_i915_gem_object *obj;
	struct intel_ring_buffer *ring = NULL;
	struct timespec timeout_stack, *timeout = NULL;
	unsigned reset_counter;
	u32 seqno = 0;
	int ret = 0;

	if (args->timeout_ns >= 0) {
		timeout_stack = ns_to_timespec(args->timeout_ns);
		timeout = &timeout_stack;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret)
		return ret;

	obj = to_intel_bo(drm_gem_object_lookup(dev, file, args->bo_handle));
	if (&obj->base == NULL) {
		mutex_unlock(&dev->struct_mutex);
		return -ENOENT;
	}

	/* Need to make sure the object gets inactive eventually. */
	ret = i915_gem_object_flush_active(obj);
	if (ret)
		goto out;

	if (obj->active) {
		seqno = obj->last_read_seqno;
		ring = obj->ring;
	}

	if (seqno == 0)
		 goto out;

	/* Do this after OLR check to make sure we make forward progress polling
	 * on this IOCTL with a 0 timeout (like busy ioctl)
	 */
	if (!args->timeout_ns) {
		ret = -ETIME;
		goto out;
	}

	drm_gem_object_unreference(&obj->base);
	reset_counter = atomic_read(&dev_priv->gpu_error.reset_counter);
	mutex_unlock(&dev->struct_mutex);

	ret = __wait_seqno(ring, seqno, reset_counter, true, timeout);
	if (timeout) {
		WARN_ON(!timespec_valid(timeout));
		args->timeout_ns = timespec_to_ns(timeout);
	}
	return ret;

out:
	drm_gem_object_unreference(&obj->base);
	mutex_unlock(&dev->struct_mutex);
	return ret;
}