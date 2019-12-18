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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_3__ {scalar_t__ cur_delay; scalar_t__ max_delay; scalar_t__ min_delay; } ;
struct TYPE_4__ {TYPE_1__ ips; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MEMINTRSTS ; 
 scalar_t__ MEMINT_EVAL_CHG ; 
 int /*<<< orphan*/  RCBMAXAVG ; 
 int /*<<< orphan*/  RCBMINAVG ; 
 int /*<<< orphan*/  RCPREVBSYTDNAVG ; 
 int /*<<< orphan*/  RCPREVBSYTUPAVG ; 
 scalar_t__ ironlake_set_drps (struct drm_device*,scalar_t__) ; 
 int /*<<< orphan*/  mchdev_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ironlake_handle_rps_change(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	u32 busy_up, busy_down, max_avg, min_avg;
	u8 new_delay;
	unsigned long flags;

	spin_lock_irqsave(&mchdev_lock, flags);

	I915_WRITE16(MEMINTRSTS, I915_READ(MEMINTRSTS));

	new_delay = dev_priv->ips.cur_delay;

	I915_WRITE16(MEMINTRSTS, MEMINT_EVAL_CHG);
	busy_up = I915_READ(RCPREVBSYTUPAVG);
	busy_down = I915_READ(RCPREVBSYTDNAVG);
	max_avg = I915_READ(RCBMAXAVG);
	min_avg = I915_READ(RCBMINAVG);

	/* Handle RCS change request from hw */
	if (busy_up > max_avg) {
		if (dev_priv->ips.cur_delay != dev_priv->ips.max_delay)
			new_delay = dev_priv->ips.cur_delay - 1;
		if (new_delay < dev_priv->ips.max_delay)
			new_delay = dev_priv->ips.max_delay;
	} else if (busy_down < min_avg) {
		if (dev_priv->ips.cur_delay != dev_priv->ips.min_delay)
			new_delay = dev_priv->ips.cur_delay + 1;
		if (new_delay > dev_priv->ips.min_delay)
			new_delay = dev_priv->ips.min_delay;
	}

	if (ironlake_set_drps(dev, new_delay))
		dev_priv->ips.cur_delay = new_delay;

	spin_unlock_irqrestore(&mchdev_lock, flags);

	return;
}