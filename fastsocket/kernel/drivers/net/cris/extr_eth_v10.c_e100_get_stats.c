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
struct net_device_stats {int dummy; } ;
struct net_local {struct net_device_stats stats; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_rx_stats (struct net_device_stats*) ; 
 int /*<<< orphan*/  update_tx_stats (struct net_device_stats*) ; 

__attribute__((used)) static struct net_device_stats *
e100_get_stats(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&lp->lock, flags);

	update_rx_stats(&lp->stats);
	update_tx_stats(&lp->stats);

	spin_unlock_irqrestore(&lp->lock, flags);
	return &lp->stats;
}