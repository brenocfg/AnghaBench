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
struct wan_device {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct cycx_x25_channel {struct net_device* slave; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct net_device *
	cycx_x25_get_dev_by_dte_addr(struct wan_device *wandev, char *dte)
{
	struct net_device *dev = wandev->dev;
	struct cycx_x25_channel *chan;

	while (dev) {
		chan = netdev_priv(dev);

		if (!strcmp(chan->addr, dte))
			break;
		dev = chan->slave;
	}
	return dev;
}