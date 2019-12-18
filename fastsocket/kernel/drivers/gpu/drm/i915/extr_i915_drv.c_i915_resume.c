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
struct TYPE_2__ {int /*<<< orphan*/  header; } ;
struct drm_i915_private {TYPE_1__ opregion; } ;
struct drm_device {scalar_t__ switch_power_state; int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/  pdev; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int EIO ; 
 int __i915_drm_thaw (struct drm_device*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_restore_gtt_mappings (struct drm_device*) ; 
 int /*<<< orphan*/  intel_gt_reset (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_enable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

int i915_resume(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	if (dev->switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	if (pci_enable_device(dev->pdev))
		return -EIO;

	pci_set_master(dev->pdev);

	intel_gt_reset(dev);

	/*
	 * Platforms with opregion should have sane BIOS, older ones (gen3 and
	 * earlier) need this since the BIOS might clear all our scratch PTEs.
	 */
	if (drm_core_check_feature(dev, DRIVER_MODESET) &&
	    !dev_priv->opregion.header) {
		mutex_lock(&dev->struct_mutex);
		i915_gem_restore_gtt_mappings(dev);
		mutex_unlock(&dev->struct_mutex);
	}

	ret = __i915_drm_thaw(dev);
	if (ret)
		return ret;

	drm_kms_helper_poll_enable(dev);
	return 0;
}