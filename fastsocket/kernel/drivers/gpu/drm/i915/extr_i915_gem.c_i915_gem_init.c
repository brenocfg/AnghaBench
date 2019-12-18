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
struct TYPE_2__ {int allow_batchbuffer; } ;
struct drm_i915_private {TYPE_1__ dri1; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_cleanup_aliasing_ppgtt (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_init_global_gtt (struct drm_device*) ; 
 int i915_gem_init_hw (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	mutex_lock(&dev->struct_mutex);
	i915_gem_init_global_gtt(dev);
	ret = i915_gem_init_hw(dev);
	mutex_unlock(&dev->struct_mutex);
	if (ret) {
		i915_gem_cleanup_aliasing_ppgtt(dev);
		return ret;
	}

	/* Allow hardware batchbuffers unless told otherwise, but not for KMS. */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		dev_priv->dri1.allow_batchbuffer = 1;
	return 0;
}