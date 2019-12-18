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
struct net_device {int dummy; } ;
struct de_private {struct net_device_stats net_stats; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __de_get_stats (struct de_private*) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *de_get_stats(struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);

	/* The chip only need report frame silently dropped. */
	spin_lock_irq(&de->lock);
 	if (netif_running(dev) && netif_device_present(dev))
 		__de_get_stats(de);
	spin_unlock_irq(&de->lock);

	return &de->net_stats;
}