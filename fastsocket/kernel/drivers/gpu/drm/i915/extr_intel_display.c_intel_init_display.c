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
struct TYPE_3__ {int /*<<< orphan*/  queue_flip; void* write_eld; int /*<<< orphan*/  modeset_global_resources; int /*<<< orphan*/  fdi_link_train; int /*<<< orphan*/  get_display_clock_speed; void* update_plane; int /*<<< orphan*/  off; int /*<<< orphan*/  crtc_disable; int /*<<< orphan*/  crtc_enable; int /*<<< orphan*/  crtc_mode_set; } ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 scalar_t__ HAS_DDI (struct drm_device*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_845G (struct drm_device*) ; 
 scalar_t__ IS_G33 (struct drm_device*) ; 
 scalar_t__ IS_G4X (struct drm_device*) ; 
 scalar_t__ IS_GEN5 (struct drm_device*) ; 
 scalar_t__ IS_GEN6 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 scalar_t__ IS_I85X (struct drm_device*) ; 
 scalar_t__ IS_I865G (struct drm_device*) ; 
 scalar_t__ IS_I915G (struct drm_device*) ; 
 scalar_t__ IS_I915GM (struct drm_device*) ; 
 scalar_t__ IS_I945G (struct drm_device*) ; 
 scalar_t__ IS_I945GM (struct drm_device*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_device*) ; 
 scalar_t__ IS_PINEVIEW_M (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 void* g4x_write_eld ; 
 int /*<<< orphan*/  gen6_fdi_link_train ; 
 int /*<<< orphan*/  haswell_crtc_disable ; 
 int /*<<< orphan*/  haswell_crtc_enable ; 
 int /*<<< orphan*/  haswell_crtc_mode_set ; 
 int /*<<< orphan*/  haswell_crtc_off ; 
 int /*<<< orphan*/  haswell_modeset_global_resources ; 
 void* haswell_write_eld ; 
 int /*<<< orphan*/  hsw_fdi_link_train ; 
 int /*<<< orphan*/  i830_get_display_clock_speed ; 
 int /*<<< orphan*/  i855_get_display_clock_speed ; 
 int /*<<< orphan*/  i865_get_display_clock_speed ; 
 int /*<<< orphan*/  i915_get_display_clock_speed ; 
 int /*<<< orphan*/  i915gm_get_display_clock_speed ; 
 int /*<<< orphan*/  i945_get_display_clock_speed ; 
 int /*<<< orphan*/  i9xx_crtc_disable ; 
 int /*<<< orphan*/  i9xx_crtc_enable ; 
 int /*<<< orphan*/  i9xx_crtc_mode_set ; 
 int /*<<< orphan*/  i9xx_crtc_off ; 
 int /*<<< orphan*/  i9xx_misc_get_display_clock_speed ; 
 void* i9xx_update_plane ; 
 int /*<<< orphan*/  intel_default_queue_flip ; 
 int /*<<< orphan*/  intel_gen2_queue_flip ; 
 int /*<<< orphan*/  intel_gen3_queue_flip ; 
 int /*<<< orphan*/  intel_gen4_queue_flip ; 
 int /*<<< orphan*/  intel_gen6_queue_flip ; 
 int /*<<< orphan*/  intel_gen7_queue_flip ; 
 int /*<<< orphan*/  ironlake_crtc_disable ; 
 int /*<<< orphan*/  ironlake_crtc_enable ; 
 int /*<<< orphan*/  ironlake_crtc_mode_set ; 
 int /*<<< orphan*/  ironlake_crtc_off ; 
 int /*<<< orphan*/  ironlake_fdi_link_train ; 
 void* ironlake_update_plane ; 
 void* ironlake_write_eld ; 
 int /*<<< orphan*/  ivb_manual_fdi_link_train ; 
 int /*<<< orphan*/  ivb_modeset_global_resources ; 
 int /*<<< orphan*/  valleyview_get_display_clock_speed ; 

__attribute__((used)) static void intel_init_display(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	/* We always want a DPMS function */
	if (HAS_DDI(dev)) {
		dev_priv->display.crtc_mode_set = haswell_crtc_mode_set;
		dev_priv->display.crtc_enable = haswell_crtc_enable;
		dev_priv->display.crtc_disable = haswell_crtc_disable;
		dev_priv->display.off = haswell_crtc_off;
		dev_priv->display.update_plane = ironlake_update_plane;
	} else if (HAS_PCH_SPLIT(dev)) {
		dev_priv->display.crtc_mode_set = ironlake_crtc_mode_set;
		dev_priv->display.crtc_enable = ironlake_crtc_enable;
		dev_priv->display.crtc_disable = ironlake_crtc_disable;
		dev_priv->display.off = ironlake_crtc_off;
		dev_priv->display.update_plane = ironlake_update_plane;
	} else {
		dev_priv->display.crtc_mode_set = i9xx_crtc_mode_set;
		dev_priv->display.crtc_enable = i9xx_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
		dev_priv->display.off = i9xx_crtc_off;
		dev_priv->display.update_plane = i9xx_update_plane;
	}

	/* Returns the core display clock speed */
	if (IS_VALLEYVIEW(dev))
		dev_priv->display.get_display_clock_speed =
			valleyview_get_display_clock_speed;
	else if (IS_I945G(dev) || (IS_G33(dev) && !IS_PINEVIEW_M(dev)))
		dev_priv->display.get_display_clock_speed =
			i945_get_display_clock_speed;
	else if (IS_I915G(dev))
		dev_priv->display.get_display_clock_speed =
			i915_get_display_clock_speed;
	else if (IS_I945GM(dev) || IS_845G(dev) || IS_PINEVIEW_M(dev))
		dev_priv->display.get_display_clock_speed =
			i9xx_misc_get_display_clock_speed;
	else if (IS_I915GM(dev))
		dev_priv->display.get_display_clock_speed =
			i915gm_get_display_clock_speed;
	else if (IS_I865G(dev))
		dev_priv->display.get_display_clock_speed =
			i865_get_display_clock_speed;
	else if (IS_I85X(dev))
		dev_priv->display.get_display_clock_speed =
			i855_get_display_clock_speed;
	else /* 852, 830 */
		dev_priv->display.get_display_clock_speed =
			i830_get_display_clock_speed;

	if (HAS_PCH_SPLIT(dev)) {
		if (IS_GEN5(dev)) {
			dev_priv->display.fdi_link_train = ironlake_fdi_link_train;
			dev_priv->display.write_eld = ironlake_write_eld;
		} else if (IS_GEN6(dev)) {
			dev_priv->display.fdi_link_train = gen6_fdi_link_train;
			dev_priv->display.write_eld = ironlake_write_eld;
		} else if (IS_IVYBRIDGE(dev)) {
			/* FIXME: detect B0+ stepping and use auto training */
			dev_priv->display.fdi_link_train = ivb_manual_fdi_link_train;
			dev_priv->display.write_eld = ironlake_write_eld;
			dev_priv->display.modeset_global_resources =
				ivb_modeset_global_resources;
		} else if (IS_HASWELL(dev)) {
			dev_priv->display.fdi_link_train = hsw_fdi_link_train;
			dev_priv->display.write_eld = haswell_write_eld;
			dev_priv->display.modeset_global_resources =
				haswell_modeset_global_resources;
		}
	} else if (IS_G4X(dev)) {
		dev_priv->display.write_eld = g4x_write_eld;
	}

	/* Default just returns -ENODEV to indicate unsupported */
	dev_priv->display.queue_flip = intel_default_queue_flip;

	switch (INTEL_INFO(dev)->gen) {
	case 2:
		dev_priv->display.queue_flip = intel_gen2_queue_flip;
		break;

	case 3:
		dev_priv->display.queue_flip = intel_gen3_queue_flip;
		break;

	case 4:
	case 5:
		dev_priv->display.queue_flip = intel_gen4_queue_flip;
		break;

	case 6:
		dev_priv->display.queue_flip = intel_gen6_queue_flip;
		break;
	case 7:
		dev_priv->display.queue_flip = intel_gen7_queue_flip;
		break;
	}
}