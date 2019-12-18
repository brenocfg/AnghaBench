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
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  error_work; } ;
struct TYPE_4__ {TYPE_1__ l3_parity; int /*<<< orphan*/  wq; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  gt_irq_mask; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  GTIMR ; 
 int /*<<< orphan*/  GT_GEN7_L3_PARITY_ERROR_INTERRUPT ; 
 int /*<<< orphan*/  HAS_L3_GPU_CACHE (struct drm_device*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ivybridge_handle_parity_error(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	unsigned long flags;

	if (!HAS_L3_GPU_CACHE(dev))
		return;

	spin_lock_irqsave(&dev_priv->irq_lock, flags);
	dev_priv->gt_irq_mask |= GT_GEN7_L3_PARITY_ERROR_INTERRUPT;
	I915_WRITE(GTIMR, dev_priv->gt_irq_mask);
	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);

	queue_work(dev_priv->wq, &dev_priv->l3_parity.error_work);
}