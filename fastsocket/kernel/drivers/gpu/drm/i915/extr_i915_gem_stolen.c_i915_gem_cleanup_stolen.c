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
struct TYPE_2__ {int /*<<< orphan*/  stolen; } ;
struct drm_i915_private {TYPE_1__ mm; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_stolen_cleanup_compression (struct drm_device*) ; 

void i915_gem_cleanup_stolen(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	i915_gem_stolen_cleanup_compression(dev);
	drm_mm_takedown(&dev_priv->mm.stolen);
}