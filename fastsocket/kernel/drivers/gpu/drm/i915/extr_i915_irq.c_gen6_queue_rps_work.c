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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_iir; } ;
struct drm_i915_private {TYPE_1__ rps; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMIMR ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gen6_queue_rps_work(struct drm_i915_private *dev_priv,
				u32 pm_iir)
{
	unsigned long flags;

	/*
	 * IIR bits should never already be set because IMR should
	 * prevent an interrupt from being shown in IIR. The warning
	 * displays a case where we've unsafely cleared
	 * dev_priv->rps.pm_iir. Although missing an interrupt of the same
	 * type is not a problem, it displays a problem in the logic.
	 *
	 * The mask bit in IMR is cleared by dev_priv->rps.work.
	 */

	spin_lock_irqsave(&dev_priv->rps.lock, flags);
	dev_priv->rps.pm_iir |= pm_iir;
	I915_WRITE(GEN6_PMIMR, dev_priv->rps.pm_iir);
	POSTING_READ(GEN6_PMIMR);
	spin_unlock_irqrestore(&dev_priv->rps.lock, flags);

	queue_work(dev_priv->wq, &dev_priv->rps.work);
}