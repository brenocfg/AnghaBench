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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitrate; int /*<<< orphan*/  tq; } ;
struct can_priv {int /*<<< orphan*/  restart_timer; TYPE_1__ bittiming; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  can_restart ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int open_candev(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);

	if (!priv->bittiming.tq && !priv->bittiming.bitrate) {
		dev_err(dev->dev.parent, "bit-timing not yet defined\n");
		return -EINVAL;
	}

	/* Switch carrier on if device was stopped while in bus-off state */
	if (!netif_carrier_ok(dev))
		netif_carrier_on(dev);

	setup_timer(&priv->restart_timer, can_restart, (unsigned long)dev);

	return 0;
}