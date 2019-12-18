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
struct TYPE_2__ {int /*<<< orphan*/  (* force_wake_put ) (struct drm_i915_private*) ;int /*<<< orphan*/  (* force_wake_get ) (struct drm_i915_private*) ;} ;
struct drm_i915_private {int gt_fifo_count; int /*<<< orphan*/  gt_lock; TYPE_1__ gt; scalar_t__ forcewake_count; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_GDRST ; 
 int GEN6_GRDOM_FULL ; 
 int /*<<< orphan*/  GT_FIFO_FREE_ENTRIES ; 
 int I915_READ_NOTRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_NOTRACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub2 (struct drm_i915_private*) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static int gen6_do_reset(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int	ret;
	unsigned long irqflags;

	/* Hold gt_lock across reset to prevent any register access
	 * with forcewake not set correctly
	 */
	spin_lock_irqsave(&dev_priv->gt_lock, irqflags);

	/* Reset the chip */

	/* GEN6_GDRST is not in the gt power well, no need to check
	 * for fifo space for the write or forcewake the chip for
	 * the read
	 */
	I915_WRITE_NOTRACE(GEN6_GDRST, GEN6_GRDOM_FULL);

	/* Spin waiting for the device to ack the reset request */
	ret = wait_for((I915_READ_NOTRACE(GEN6_GDRST) & GEN6_GRDOM_FULL) == 0, 500);

	/* If reset with a user forcewake, try to restore, otherwise turn it off */
	if (dev_priv->forcewake_count)
		dev_priv->gt.force_wake_get(dev_priv);
	else
		dev_priv->gt.force_wake_put(dev_priv);

	/* Restore fifo count */
	dev_priv->gt_fifo_count = I915_READ_NOTRACE(GT_FIFO_FREE_ENTRIES);

	spin_unlock_irqrestore(&dev_priv->gt_lock, irqflags);
	return ret;
}