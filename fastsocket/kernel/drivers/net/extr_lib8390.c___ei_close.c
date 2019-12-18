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
struct net_device {int dummy; } ;
struct ei_device {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NS8390_init (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __ei_close(struct net_device *dev)
{
	struct ei_device *ei_local = (struct ei_device *) netdev_priv(dev);
	unsigned long flags;

	/*
	 *	Hold the page lock during close
	 */

      	spin_lock_irqsave(&ei_local->page_lock, flags);
	__NS8390_init(dev, 0);
      	spin_unlock_irqrestore(&ei_local->page_lock, flags);
	netif_stop_queue(dev);
	return 0;
}