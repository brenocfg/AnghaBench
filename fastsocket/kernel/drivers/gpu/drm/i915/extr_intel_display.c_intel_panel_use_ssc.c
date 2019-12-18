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
struct drm_i915_private {int quirks; scalar_t__ lvds_use_ssc; } ;

/* Variables and functions */
 int QUIRK_LVDS_SSC_DISABLE ; 
 scalar_t__ i915_panel_use_ssc ; 

__attribute__((used)) static inline bool intel_panel_use_ssc(struct drm_i915_private *dev_priv)
{
	if (i915_panel_use_ssc >= 0)
		return i915_panel_use_ssc != 0;
	return dev_priv->lvds_use_ssc
		&& !(dev_priv->quirks & QUIRK_LVDS_SSC_DISABLE);
}