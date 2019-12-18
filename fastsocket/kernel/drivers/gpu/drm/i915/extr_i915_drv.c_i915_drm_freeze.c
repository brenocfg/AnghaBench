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
struct TYPE_3__ {int /*<<< orphan*/  delayed_resume_work; } ;
struct drm_i915_private {int enable_hotplug_processing; TYPE_1__ rps; int /*<<< orphan*/  modeset_restore_lock; int /*<<< orphan*/  modeset_restore; } ;
struct drm_device {TYPE_2__* pdev; struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  MODESET_SUSPENDED ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int i915_gem_idle (struct drm_device*) ; 
 int /*<<< orphan*/  i915_save_state (struct drm_device*) ; 
 int /*<<< orphan*/  intel_fbdev_set_suspend (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_modeset_disable (struct drm_device*) ; 
 int /*<<< orphan*/  intel_opregion_fini (struct drm_device*) ; 
 int /*<<< orphan*/  intel_set_power_well (struct drm_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_save_state (TYPE_2__*) ; 

__attribute__((used)) static int i915_drm_freeze(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* ignore lid events during suspend */
	mutex_lock(&dev_priv->modeset_restore_lock);
	dev_priv->modeset_restore = MODESET_SUSPENDED;
	mutex_unlock(&dev_priv->modeset_restore_lock);

	intel_set_power_well(dev, true);

	drm_kms_helper_poll_disable(dev);

	pci_save_state(dev->pdev);

	/* If KMS is active, we do the leavevt stuff here */
	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		int error = i915_gem_idle(dev);
		if (error) {
			dev_err(&dev->pdev->dev,
				"GEM idle failed, resume might fail\n");
			return error;
		}

		cancel_delayed_work_sync(&dev_priv->rps.delayed_resume_work);

		intel_modeset_disable(dev);

		drm_irq_uninstall(dev);
		dev_priv->enable_hotplug_processing = false;
	}

	i915_save_state(dev);

	intel_opregion_fini(dev);

	console_lock();
	intel_fbdev_set_suspend(dev, 1);
	console_unlock();

	return 0;
}