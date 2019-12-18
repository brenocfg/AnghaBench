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
struct TYPE_3__ {int /*<<< orphan*/  stolen_size; } ;
struct TYPE_4__ {scalar_t__ stolen_base; int /*<<< orphan*/  stolen; } ;
struct drm_i915_private {TYPE_1__ gtt; TYPE_2__ mm; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_stolen_to_physical (struct drm_device*) ; 

int i915_gem_init_stolen(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	dev_priv->mm.stolen_base = i915_stolen_to_physical(dev);
	if (dev_priv->mm.stolen_base == 0)
		return 0;

	DRM_DEBUG_KMS("found %zd bytes of stolen memory at %08lx\n",
		      dev_priv->gtt.stolen_size, dev_priv->mm.stolen_base);

	/* Basic memrange allocator for stolen space */
	drm_mm_init(&dev_priv->mm.stolen, 0, dev_priv->gtt.stolen_size);

	return 0;
}