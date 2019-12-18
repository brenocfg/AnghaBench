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
struct drm_i915_private {int enable_hotplug_processing; TYPE_1__ mm; int /*<<< orphan*/  console_resume_work; } ;
struct drm_device {int vblank_disable_allowed; int /*<<< orphan*/  pdev; int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_irq_install (struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_aliasing_ppgtt (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_ringbuffer (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_stolen (struct drm_device*) ; 
 int i915_gem_init (struct drm_device*) ; 
 int i915_gem_init_stolen (struct drm_device*) ; 
 int /*<<< orphan*/  i915_switcheroo_ops ; 
 int /*<<< orphan*/ * i915_vga_set_decode ; 
 int /*<<< orphan*/  intel_console_resume ; 
 int intel_fbdev_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_fbdev_initial_config (struct drm_device*) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_modeset_gem_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_modeset_init (struct drm_device*) ; 
 int intel_parse_bios (struct drm_device*) ; 
 int /*<<< orphan*/  intel_register_dsm_handler () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vga_client_register (int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vga_switcheroo_register_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_load_modeset_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ret = intel_parse_bios(dev);
	if (ret)
		DRM_INFO("failed to find VBIOS tables\n");

	/* If we have > 1 VGA cards, then we need to arbitrate access
	 * to the common VGA resources.
	 *
	 * If we are a secondary display controller (!PCI_DISPLAY_CLASS_VGA),
	 * then we do not take part in VGA arbitration and the
	 * vga_client_register() fails with -ENODEV.
	 */
	ret = vga_client_register(dev->pdev, dev, NULL, i915_vga_set_decode);
	if (ret && ret != -ENODEV)
		goto out;

	intel_register_dsm_handler();

	ret = vga_switcheroo_register_client(dev->pdev, &i915_switcheroo_ops);
	if (ret)
		goto cleanup_vga_client;

	/* Initialise stolen first so that we may reserve preallocated
	 * objects for the BIOS to KMS transition.
	 */
	ret = i915_gem_init_stolen(dev);
	if (ret)
		goto cleanup_vga_switcheroo;

	ret = drm_irq_install(dev);
	if (ret)
		goto cleanup_gem_stolen;

	/* Important: The output setup functions called by modeset_init need
	 * working irqs for e.g. gmbus and dp aux transfers. */
	intel_modeset_init(dev);

	ret = i915_gem_init(dev);
	if (ret)
		goto cleanup_irq;

	INIT_WORK(&dev_priv->console_resume_work, intel_console_resume);

	intel_modeset_gem_init(dev);

	/* Always safe in the mode setting case. */
	/* FIXME: do pre/post-mode set stuff in core KMS code */
	dev->vblank_disable_allowed = 1;

	ret = intel_fbdev_init(dev);
	if (ret)
		goto cleanup_gem;

	/* Only enable hotplug handling once the fbdev is fully set up. */
	intel_hpd_init(dev);

	/*
	 * Some ports require correctly set-up hpd registers for detection to
	 * work properly (leading to ghost connected connector status), e.g. VGA
	 * on gm45.  Hence we can only set up the initial fbdev config after hpd
	 * irqs are fully enabled. Now we should scan for the initial config
	 * only once hotplug handling is enabled, but due to screwed-up locking
	 * around kms/fbdev init we can't protect the fdbev initial config
	 * scanning against hotplug events. Hence do this first and ignore the
	 * tiny window where we will loose hotplug notifactions.
	 */
	intel_fbdev_initial_config(dev);

	/* Only enable hotplug handling once the fbdev is fully set up. */
	dev_priv->enable_hotplug_processing = true;

	drm_kms_helper_poll_init(dev);

	/* We're off and running w/KMS */
	dev_priv->mm.suspended = 0;

	return 0;

cleanup_gem:
	mutex_lock(&dev->struct_mutex);
	i915_gem_cleanup_ringbuffer(dev);
	mutex_unlock(&dev->struct_mutex);
	i915_gem_cleanup_aliasing_ppgtt(dev);
cleanup_irq:
	drm_irq_uninstall(dev);
cleanup_gem_stolen:
	i915_gem_cleanup_stolen(dev);
cleanup_vga_switcheroo:
	vga_switcheroo_unregister_client(dev->pdev);
cleanup_vga_client:
	vga_client_register(dev->pdev, NULL, NULL, NULL);
out:
	return ret;
}