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
struct TYPE_2__ {scalar_t__ suspended; } ;
struct drm_i915_private {int enable_hotplug_processing; int /*<<< orphan*/  modeset_restore_lock; int /*<<< orphan*/  modeset_restore; int /*<<< orphan*/  console_resume_work; TYPE_1__ mm; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  MODESET_DONE ; 
 scalar_t__ console_trylock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_irq_install (struct drm_device*) ; 
 int i915_gem_init_hw (struct drm_device*) ; 
 int /*<<< orphan*/  i915_restore_state (struct drm_device*) ; 
 int /*<<< orphan*/  intel_fbdev_set_suspend (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_pch_refclk (struct drm_device*) ; 
 int /*<<< orphan*/  intel_modeset_init_hw (struct drm_device*) ; 
 int /*<<< orphan*/  intel_modeset_setup_hw_state (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_opregion_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_opregion_setup (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __i915_drm_thaw(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int error = 0;

	i915_restore_state(dev);
	intel_opregion_setup(dev);

	/* KMS EnterVT equivalent */
	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		intel_init_pch_refclk(dev);

		mutex_lock(&dev->struct_mutex);
		dev_priv->mm.suspended = 0;

		error = i915_gem_init_hw(dev);
		mutex_unlock(&dev->struct_mutex);

		/* We need working interrupts for modeset enabling ... */
		drm_irq_install(dev);

		intel_modeset_init_hw(dev);
		intel_modeset_setup_hw_state(dev, false);

		/*
		 * ... but also need to make sure that hotplug processing
		 * doesn't cause havoc. Like in the driver load code we don't
		 * bother with the tiny race here where we might loose hotplug
		 * notifications.
		 * */
		intel_hpd_init(dev);
		dev_priv->enable_hotplug_processing = true;
	}

	intel_opregion_init(dev);

	/*
	 * The console lock can be pretty contented on resume due
	 * to all the printk activity.  Try to keep it out of the hot
	 * path of resume if possible.
	 */
	if (console_trylock()) {
		intel_fbdev_set_suspend(dev, 0);
		console_unlock();
	} else {
		schedule_work(&dev_priv->console_resume_work);
	}

	mutex_lock(&dev_priv->modeset_restore_lock);
	dev_priv->modeset_restore = MODESET_DONE;
	mutex_unlock(&dev_priv->modeset_restore_lock);
	return error;
}