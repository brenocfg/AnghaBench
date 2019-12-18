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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int /*<<< orphan*/  mcast_work; int /*<<< orphan*/  driver_lock; scalar_t__ infra_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_NET ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_eth_stop(struct net_device *dev)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_NET);

	spin_lock_irq(&priv->driver_lock);
	priv->infra_open = 0;
	netif_stop_queue(dev);
	spin_unlock_irq(&priv->driver_lock);

	schedule_work(&priv->mcast_work);

	lbs_deb_leave(LBS_DEB_NET);
	return 0;
}