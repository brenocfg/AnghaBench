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
struct TYPE_4__ {int /*<<< orphan*/  mappable_base; } ;
struct drm_i915_private {int num_pipe; TYPE_2__ gtt; } ;
struct TYPE_3__ {int preferred_depth; int prefer_shadow; int max_width; int max_height; int /*<<< orphan*/  fb_base; int /*<<< orphan*/ * funcs; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {TYPE_1__ mode_config; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_GEN3 (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  i915_disable_vga (struct drm_device*) ; 
 int /*<<< orphan*/  intel_cpu_pll_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_crtc_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_disable_fbc (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_display (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_pm (struct drm_device*) ; 
 int /*<<< orphan*/  intel_init_quirks (struct drm_device*) ; 
 int /*<<< orphan*/  intel_mode_funcs ; 
 int /*<<< orphan*/  intel_pch_pll_init (struct drm_device*) ; 
 int intel_plane_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  intel_setup_outputs (struct drm_device*) ; 

void intel_modeset_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i, ret;

	drm_mode_config_init(dev);

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	dev->mode_config.preferred_depth = 24;
	dev->mode_config.prefer_shadow = 1;

	dev->mode_config.funcs = &intel_mode_funcs;

	intel_init_quirks(dev);

	intel_init_pm(dev);

	intel_init_display(dev);

	if (IS_GEN2(dev)) {
		dev->mode_config.max_width = 2048;
		dev->mode_config.max_height = 2048;
	} else if (IS_GEN3(dev)) {
		dev->mode_config.max_width = 4096;
		dev->mode_config.max_height = 4096;
	} else {
		dev->mode_config.max_width = 8192;
		dev->mode_config.max_height = 8192;
	}
	dev->mode_config.fb_base = dev_priv->gtt.mappable_base;

	DRM_DEBUG_KMS("%d display pipe%s available.\n",
		      dev_priv->num_pipe, dev_priv->num_pipe > 1 ? "s" : "");

	for (i = 0; i < dev_priv->num_pipe; i++) {
		intel_crtc_init(dev, i);
		ret = intel_plane_init(dev, i);
		if (ret)
			DRM_DEBUG_KMS("plane %d init failed: %d\n", i, ret);
	}

	intel_cpu_pll_init(dev);
	intel_pch_pll_init(dev);

	/* Just disable it once at startup */
	i915_disable_vga(dev);
	intel_setup_outputs(dev);

	/* Just in case the BIOS is doing something questionable. */
	intel_disable_fbc(dev);
}