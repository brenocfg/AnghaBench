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
struct sir_driver {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* stop_dev ) (struct sir_dev*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  sem; } ;
struct sir_dev {TYPE_1__ fsm; scalar_t__ speed; int /*<<< orphan*/  priv; struct sir_driver* drv; int /*<<< orphan*/ * irlap; int /*<<< orphan*/  enable_rx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irlap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct sir_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  sirdev_free_buffers (struct sir_dev*) ; 
 int /*<<< orphan*/  stub1 (struct sir_dev*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirdev_close(struct net_device *ndev)
{
	struct sir_dev *dev = netdev_priv(ndev);
	const struct sir_driver *drv;

//	IRDA_DEBUG(0, "%s\n", __func__);

	netif_stop_queue(ndev);

	down(&dev->fsm.sem);		/* block on pending config completion */

	atomic_set(&dev->enable_rx, 0);

	if (unlikely(!dev->irlap))
		goto out;
	irlap_close(dev->irlap);
	dev->irlap = NULL;

	drv = dev->drv;
	if (unlikely(!drv  ||  !dev->priv))
		goto out;

	if (drv->stop_dev)
		drv->stop_dev(dev);

	sirdev_free_buffers(dev);
	module_put(drv->owner);

out:
	dev->speed = 0;
	up(&dev->fsm.sem);
	return 0;
}