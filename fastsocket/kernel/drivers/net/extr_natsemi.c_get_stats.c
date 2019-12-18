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
struct netdev_private {struct net_device_stats stats; int /*<<< orphan*/  lock; int /*<<< orphan*/  hands_off; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_stats (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *get_stats(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);

	/* The chip only need report frame silently dropped. */
	spin_lock_irq(&np->lock);
	if (netif_running(dev) && !np->hands_off)
		__get_stats(dev);
	spin_unlock_irq(&np->lock);

	return &np->stats;
}