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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_off; } ;
struct can_priv {int restart_ms; int /*<<< orphan*/  restart_timer; TYPE_2__ can_stats; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

void can_bus_off(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);

	dev_dbg(dev->dev.parent, "bus-off\n");

	netif_carrier_off(dev);
	priv->can_stats.bus_off++;

	if (priv->restart_ms)
		mod_timer(&priv->restart_timer,
			  jiffies + (priv->restart_ms * HZ) / 1000);
}