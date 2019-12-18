#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct gem {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; scalar_t__ status; scalar_t__ regs; int /*<<< orphan*/  running; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ GREG_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gem_disable_ints (struct gem*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t gem_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct gem *gp = netdev_priv(dev);
	unsigned long flags;

	/* Swallow interrupts when shutting the chip down, though
	 * that shouldn't happen, we should have done free_irq() at
	 * this point...
	 */
	if (!gp->running)
		return IRQ_HANDLED;

	spin_lock_irqsave(&gp->lock, flags);

	if (napi_schedule_prep(&gp->napi)) {
		u32 gem_status = readl(gp->regs + GREG_STAT);

		if (gem_status == 0) {
			napi_enable(&gp->napi);
			spin_unlock_irqrestore(&gp->lock, flags);
			return IRQ_NONE;
		}
		gp->status = gem_status;
		gem_disable_ints(gp);
		__napi_schedule(&gp->napi);
	}

	spin_unlock_irqrestore(&gp->lock, flags);

	/* If polling was disabled at the time we received that
	 * interrupt, we may return IRQ_HANDLED here while we
	 * should return IRQ_NONE. No big deal...
	 */
	return IRQ_HANDLED;
}