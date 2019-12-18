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
struct gem {int /*<<< orphan*/  lock; TYPE_1__* pdev; int /*<<< orphan*/  tx_lock; scalar_t__ running; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gem_clean_rings (struct gem*) ; 
 int /*<<< orphan*/  gem_disable_ints (struct gem*) ; 
 int /*<<< orphan*/  gem_put_cell (struct gem*) ; 
 int /*<<< orphan*/  gem_reset (struct gem*) ; 
 int /*<<< orphan*/  gem_stop_dma (struct gem*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gem_do_stop(struct net_device *dev, int wol)
{
	struct gem *gp = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&gp->lock, flags);
	spin_lock(&gp->tx_lock);

	gp->running = 0;

	/* Stop netif queue */
	netif_stop_queue(dev);

	/* Make sure ints are disabled */
	gem_disable_ints(gp);

	/* We can drop the lock now */
	spin_unlock(&gp->tx_lock);
	spin_unlock_irqrestore(&gp->lock, flags);

	/* If we are going to sleep with WOL */
	gem_stop_dma(gp);
	msleep(10);
	if (!wol)
		gem_reset(gp);
	msleep(10);

	/* Get rid of rings */
	gem_clean_rings(gp);

	/* No irq needed anymore */
	free_irq(gp->pdev->irq, (void *) dev);

	/* Cell not needed neither if no WOL */
	if (!wol) {
		spin_lock_irqsave(&gp->lock, flags);
		gem_put_cell(gp);
		spin_unlock_irqrestore(&gp->lock, flags);
	}
}