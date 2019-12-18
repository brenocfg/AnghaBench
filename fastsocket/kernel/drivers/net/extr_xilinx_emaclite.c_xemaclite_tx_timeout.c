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
struct net_local {int /*<<< orphan*/  reset_lock; int /*<<< orphan*/ * deferred_skb; TYPE_1__* ndev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {int trans_start; TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long TX_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xemaclite_disable_interrupts (struct net_local*) ; 
 int /*<<< orphan*/  xemaclite_enable_interrupts (struct net_local*) ; 

__attribute__((used)) static void xemaclite_tx_timeout(struct net_device *dev)
{
	struct net_local *lp = (struct net_local *) netdev_priv(dev);
	unsigned long flags;

	dev_err(&lp->ndev->dev, "Exceeded transmit timeout of %lu ms\n",
		TX_TIMEOUT * 1000UL / HZ);

	dev->stats.tx_errors++;

	/* Reset the device */
	spin_lock_irqsave(&lp->reset_lock, flags);

	/* Shouldn't really be necessary, but shouldn't hurt */
	netif_stop_queue(dev);

	xemaclite_disable_interrupts(lp);
	xemaclite_enable_interrupts(lp);

	if (lp->deferred_skb) {
		dev_kfree_skb(lp->deferred_skb);
		lp->deferred_skb = NULL;
		dev->stats.tx_errors++;
	}

	/* To exclude tx timeout */
	dev->trans_start = 0xffffffff - TX_TIMEOUT - TX_TIMEOUT;

	/* We're all ready to go. Start the queue */
	netif_wake_queue(dev);
	spin_unlock_irqrestore(&lp->reset_lock, flags);
}