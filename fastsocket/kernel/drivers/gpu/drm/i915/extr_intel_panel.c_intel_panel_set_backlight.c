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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {scalar_t__ backlight_enabled; int /*<<< orphan*/  backlight_level; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_panel_actually_set_backlight (struct drm_device*,int /*<<< orphan*/ ) ; 

void intel_panel_set_backlight(struct drm_device *dev, u32 level)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->backlight_level = level;
	if (dev_priv->backlight_enabled)
		intel_panel_actually_set_backlight(dev, level);
}