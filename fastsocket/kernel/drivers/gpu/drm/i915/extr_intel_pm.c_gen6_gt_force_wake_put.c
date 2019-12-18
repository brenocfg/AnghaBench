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
struct TYPE_2__ {int /*<<< orphan*/  (* force_wake_put ) (struct drm_i915_private*) ;} ;
struct drm_i915_private {scalar_t__ forcewake_count; int /*<<< orphan*/  gt_lock; TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 

void gen6_gt_force_wake_put(struct drm_i915_private *dev_priv)
{
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);
	if (--dev_priv->forcewake_count == 0)
		dev_priv->gt.force_wake_put(dev_priv);
	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
}