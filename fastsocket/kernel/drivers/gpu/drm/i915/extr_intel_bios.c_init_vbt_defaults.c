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
struct drm_i915_private {int lvds_dither; int int_tv_support; int int_crt_support; int lvds_use_ssc; int /*<<< orphan*/  lvds_ssc_freq; int /*<<< orphan*/ * sdvo_lvds_vbt_mode; scalar_t__ lvds_vbt; int /*<<< orphan*/  crt_ddc_pin; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMBUS_PORT_VGADDC ; 
 int /*<<< orphan*/  intel_bios_ssc_frequency (struct drm_device*,int) ; 

__attribute__((used)) static void
init_vbt_defaults(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;

	dev_priv->crt_ddc_pin = GMBUS_PORT_VGADDC;

	/* LFP panel data */
	dev_priv->lvds_dither = 1;
	dev_priv->lvds_vbt = 0;

	/* SDVO panel data */
	dev_priv->sdvo_lvds_vbt_mode = NULL;

	/* general features */
	dev_priv->int_tv_support = 1;
	dev_priv->int_crt_support = 1;

	/* Default to using SSC */
	dev_priv->lvds_use_ssc = 1;
	dev_priv->lvds_ssc_freq = intel_bios_ssc_frequency(dev, 1);
	DRM_DEBUG_KMS("Set default to SSC at %dMHz\n", dev_priv->lvds_ssc_freq);
}