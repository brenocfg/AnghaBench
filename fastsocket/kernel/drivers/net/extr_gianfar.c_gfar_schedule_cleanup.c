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
struct net_device {int dummy; } ;
struct gfar_private {int /*<<< orphan*/  txlock; int /*<<< orphan*/  rxlock; TYPE_1__* regs; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  ievent; int /*<<< orphan*/  imask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEVENT_RTX_MASK ; 
 int /*<<< orphan*/  IMASK_RTX_DISABLED ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gfar_schedule_cleanup(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&priv->txlock, flags);
	spin_lock(&priv->rxlock);

	if (napi_schedule_prep(&priv->napi)) {
		gfar_write(&priv->regs->imask, IMASK_RTX_DISABLED);
		__napi_schedule(&priv->napi);
	} else {
		/*
		 * Clear IEVENT, so interrupts aren't called again
		 * because of the packets that have already arrived.
		 */
		gfar_write(&priv->regs->ievent, IEVENT_RTX_MASK);
	}

	spin_unlock(&priv->rxlock);
	spin_unlock_irqrestore(&priv->txlock, flags);
}