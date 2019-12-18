#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__* dev_private; } ;
struct TYPE_4__ {int suspended; int /*<<< orphan*/  active_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  reset_counter; } ;
struct TYPE_5__ {TYPE_1__ mm; TYPE_3__ gpu_error; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_irq_install (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_ringbuffer (struct drm_device*) ; 
 int i915_gem_init_hw (struct drm_device*) ; 
 scalar_t__ i915_reset_in_progress (TYPE_3__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
i915_gem_entervt_ioctl(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return 0;

	if (i915_reset_in_progress(&dev_priv->gpu_error)) {
		DRM_ERROR("Reenabling wedged hardware, good luck\n");
		atomic_set(&dev_priv->gpu_error.reset_counter, 0);
	}

	mutex_lock(&dev->struct_mutex);
	dev_priv->mm.suspended = 0;

	ret = i915_gem_init_hw(dev);
	if (ret != 0) {
		mutex_unlock(&dev->struct_mutex);
		return ret;
	}

	BUG_ON(!list_empty(&dev_priv->mm.active_list));
	mutex_unlock(&dev->struct_mutex);

	ret = drm_irq_install(dev);
	if (ret)
		goto cleanup_ringbuffer;

	return 0;

cleanup_ringbuffer:
	mutex_lock(&dev->struct_mutex);
	i915_gem_cleanup_ringbuffer(dev);
	dev_priv->mm.suspended = 1;
	mutex_unlock(&dev->struct_mutex);

	return ret;
}