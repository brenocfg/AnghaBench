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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_sprite_wm ) (struct drm_device*,int,int /*<<< orphan*/ ,int) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_device*,int,int /*<<< orphan*/ ,int) ; 

void intel_update_sprite_watermarks(struct drm_device *dev, int pipe,
				    uint32_t sprite_width, int pixel_size)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->display.update_sprite_wm)
		dev_priv->display.update_sprite_wm(dev, pipe, sprite_width,
						   pixel_size);
}