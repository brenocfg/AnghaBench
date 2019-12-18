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
struct net_device {struct net_device_stats stats; } ;
struct cp_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cp_get_stats (struct cp_private*) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct net_device_stats *cp_get_stats(struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned long flags;

	/* The chip only need report frame silently dropped. */
	spin_lock_irqsave(&cp->lock, flags);
 	if (netif_running(dev) && netif_device_present(dev))
 		__cp_get_stats(cp);
	spin_unlock_irqrestore(&cp->lock, flags);

	return &dev->stats;
}