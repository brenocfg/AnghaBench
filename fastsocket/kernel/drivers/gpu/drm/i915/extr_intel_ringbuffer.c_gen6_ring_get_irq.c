#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_ring_buffer {scalar_t__ id; int irq_enable_mask; int /*<<< orphan*/  irq_refcount; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  irq_enabled; TYPE_1__* dev_private; } ;
struct TYPE_3__ {int gt_irq_mask; int /*<<< orphan*/  irq_lock; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int GEN6_RENDER_L3_PARITY_ERROR ; 
 int /*<<< orphan*/  GTIMR ; 
 scalar_t__ HAS_L3_GPU_CACHE (struct drm_device*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I915_WRITE_IMR (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ RCS ; 
 int /*<<< orphan*/  gen6_gt_force_wake_get (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool
gen6_ring_get_irq(struct intel_ring_buffer *ring)
{
	struct drm_device *dev = ring->dev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	unsigned long flags;

	if (!dev->irq_enabled)
	       return false;

	/* It looks like we need to prevent the gt from suspending while waiting
	 * for an notifiy irq, otherwise irqs seem to get lost on at least the
	 * blt/bsd rings on ivb. */
	gen6_gt_force_wake_get(dev_priv);

	spin_lock_irqsave(&dev_priv->irq_lock, flags);
	if (ring->irq_refcount++ == 0) {
		if (HAS_L3_GPU_CACHE(dev) && ring->id == RCS)
			I915_WRITE_IMR(ring, ~(ring->irq_enable_mask |
						GEN6_RENDER_L3_PARITY_ERROR));
		else
			I915_WRITE_IMR(ring, ~ring->irq_enable_mask);
		dev_priv->gt_irq_mask &= ~ring->irq_enable_mask;
		I915_WRITE(GTIMR, dev_priv->gt_irq_mask);
		POSTING_READ(GTIMR);
	}
	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);

	return true;
}