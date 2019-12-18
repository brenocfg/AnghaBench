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
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct iss_net_private*) ;} ;
struct iss_net_private {int /*<<< orphan*/  lock; TYPE_1__ tp; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct iss_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  opened ; 
 int /*<<< orphan*/  opened_lock ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iss_net_private*) ; 

__attribute__((used)) static int iss_net_close(struct net_device *dev)
{
	struct iss_net_private *lp = netdev_priv(dev);
printk("iss_net_close!\n");
	netif_stop_queue(dev);
	spin_lock(&lp->lock);

	spin_lock(&opened_lock);
	list_del(&opened);
	spin_unlock(&opened_lock);

	del_timer_sync(&lp->timer);

	lp->tp.close(lp);

	spin_unlock(&lp->lock);
	return 0;
}