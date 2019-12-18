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
struct drm_i915_private {scalar_t__ backlight_level; int backlight_enabled; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ intel_panel_get_backlight (struct drm_device*) ; 

__attribute__((used)) static void intel_panel_init_backlight(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->backlight_level = intel_panel_get_backlight(dev);
	dev_priv->backlight_enabled = dev_priv->backlight_level != 0;
}