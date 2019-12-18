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
struct TYPE_2__ {int /*<<< orphan*/  (* update_linetime_wm ) (struct drm_device*,int,struct drm_display_mode*) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_device*,int,struct drm_display_mode*) ; 

void intel_update_linetime_watermarks(struct drm_device *dev,
		int pipe, struct drm_display_mode *mode)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->display.update_linetime_wm)
		dev_priv->display.update_linetime_wm(dev, pipe, mode);
}