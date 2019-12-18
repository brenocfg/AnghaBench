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
struct drm_i915_private {scalar_t__ cfb_size; scalar_t__ compressed_llb; scalar_t__ compressed_fb; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_put_block (scalar_t__) ; 

void i915_gem_stolen_cleanup_compression(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->cfb_size == 0)
		return;

	if (dev_priv->compressed_fb)
		drm_mm_put_block(dev_priv->compressed_fb);

	if (dev_priv->compressed_llb)
		drm_mm_put_block(dev_priv->compressed_llb);

	dev_priv->cfb_size = 0;
}