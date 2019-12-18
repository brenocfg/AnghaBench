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
struct net_device {int /*<<< orphan*/  irq; } ;
struct ioc3_private {int /*<<< orphan*/  ioc3_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ioc3_free_rings (struct ioc3_private*) ; 
 int /*<<< orphan*/  ioc3_stop (struct ioc3_private*) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ioc3_close(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);

	del_timer_sync(&ip->ioc3_timer);

	netif_stop_queue(dev);

	ioc3_stop(ip);
	free_irq(dev->irq, dev);

	ioc3_free_rings(ip);
	return 0;
}