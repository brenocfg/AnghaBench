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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ pm_iir; } ;
struct drm_i915_private {TYPE_1__ rps; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMIER ; 
 int /*<<< orphan*/  GEN6_PMIIR ; 
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  GEN6_RC_CONTROL ; 
 int /*<<< orphan*/  GEN6_RPNSWREQ ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen6_disable_rps(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	I915_WRITE(GEN6_RC_CONTROL, 0);
	I915_WRITE(GEN6_RPNSWREQ, 1 << 31);
	I915_WRITE(GEN6_PMINTRMSK, 0xffffffff);
	I915_WRITE(GEN6_PMIER, 0);
	/* Complete PM interrupt masking here doesn't race with the rps work
	 * item again unmasking PM interrupts because that is using a different
	 * register (PMIMR) to mask PM interrupts. The only risk is in leaving
	 * stale bits in PMIIR and PMIMR which gen6_enable_rps will clean up. */

	spin_lock_irq(&dev_priv->rps.lock);
	dev_priv->rps.pm_iir = 0;
	spin_unlock_irq(&dev_priv->rps.lock);

	I915_WRITE(GEN6_PMIIR, I915_READ(GEN6_PMIIR));
}