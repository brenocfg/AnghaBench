#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_5__ {TYPE_3__* overlay; } ;
typedef  TYPE_2__ drm_i915_private_t ;
struct TYPE_6__ {TYPE_1__* reg_bo; int /*<<< orphan*/  active; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 

void intel_cleanup_overlay(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;

	if (!dev_priv->overlay)
		return;

	/* The bo's should be free'd by the generic code already.
	 * Furthermore modesetting teardown happens beforehand so the
	 * hardware should be off already */
	BUG_ON(dev_priv->overlay->active);

	drm_gem_object_unreference_unlocked(&dev_priv->overlay->reg_bo->base);
	kfree(dev_priv->overlay);
}