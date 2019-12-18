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
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_dma_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_lastclose (struct drm_device*) ; 
 int /*<<< orphan*/  intel_fb_restore_mode (struct drm_device*) ; 
 int /*<<< orphan*/  vga_switcheroo_process_delayed_switch () ; 

void i915_driver_lastclose(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;

	/* On gen6+ we refuse to init without kms enabled, but then the drm core
	 * goes right around and calls lastclose. Check for this and don't clean
	 * up anything. */
	if (!dev_priv)
		return;

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		intel_fb_restore_mode(dev);
		vga_switcheroo_process_delayed_switch();
		return;
	}

	i915_gem_lastclose(dev);

	i915_dma_cleanup(dev);
}