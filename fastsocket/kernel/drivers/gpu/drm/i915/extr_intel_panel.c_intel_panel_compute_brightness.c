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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int quirks; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int QUIRK_INVERT_BRIGHTNESS ; 
 scalar_t__ i915_panel_invert_brightness ; 
 scalar_t__ intel_panel_get_max_backlight (struct drm_device*) ; 

__attribute__((used)) static u32 intel_panel_compute_brightness(struct drm_device *dev, u32 val)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (i915_panel_invert_brightness < 0)
		return val;

	if (i915_panel_invert_brightness > 0 ||
	    dev_priv->quirks & QUIRK_INVERT_BRIGHTNESS)
		return intel_panel_get_max_backlight(dev) - val;

	return val;
}