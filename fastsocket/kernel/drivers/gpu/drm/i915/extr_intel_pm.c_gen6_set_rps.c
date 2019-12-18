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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ max_delay; scalar_t__ min_delay; scalar_t__ cur_delay; int /*<<< orphan*/  hw_lock; } ;
struct drm_i915_private {TYPE_1__ rps; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int GEN6_AGGRESSIVE_TURBO ; 
 int GEN6_FREQUENCY (scalar_t__) ; 
 int GEN6_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_RPNSWREQ ; 
 int /*<<< orphan*/  GEN6_RP_INTERRUPT_LIMITS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int gen6_rps_limits (struct drm_i915_private*,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_intel_gpu_freq_change (scalar_t__) ; 

void gen6_set_rps(struct drm_device *dev, u8 val)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 limits = gen6_rps_limits(dev_priv, &val);

	WARN_ON(!mutex_is_locked(&dev_priv->rps.hw_lock));
	WARN_ON(val > dev_priv->rps.max_delay);
	WARN_ON(val < dev_priv->rps.min_delay);

	if (val == dev_priv->rps.cur_delay)
		return;

	I915_WRITE(GEN6_RPNSWREQ,
		   GEN6_FREQUENCY(val) |
		   GEN6_OFFSET(0) |
		   GEN6_AGGRESSIVE_TURBO);

	/* Make sure we continue to get interrupts
	 * until we hit the minimum or maximum frequencies.
	 */
	I915_WRITE(GEN6_RP_INTERRUPT_LIMITS, limits);

	POSTING_READ(GEN6_RPNSWREQ);

	dev_priv->rps.cur_delay = val;

	trace_intel_gpu_freq_change(val * 50);
}