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
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct eth_bearer {TYPE_1__* bearer; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 size_t MAX_ETH_BEARERS ; 
#define  NETDEV_CHANGE 134 
#define  NETDEV_CHANGEADDR 133 
#define  NETDEV_CHANGEMTU 132 
#define  NETDEV_CHANGENAME 131 
#define  NETDEV_DOWN 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct eth_bearer* eth_bearers ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  tipc_block_bearer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_continue (TYPE_1__*) ; 
 int /*<<< orphan*/  tipc_disable_bearer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recv_notification(struct notifier_block *nb, unsigned long evt,
			     void *dv)
{
	struct net_device *dev = (struct net_device *)dv;
	struct eth_bearer *eb_ptr = &eth_bearers[0];
	struct eth_bearer *stop = &eth_bearers[MAX_ETH_BEARERS];

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	while ((eb_ptr->dev != dev)) {
		if (++eb_ptr == stop)
			return NOTIFY_DONE;	/* couldn't find device */
	}
	if (!eb_ptr->bearer)
		return NOTIFY_DONE;		/* bearer had been disabled */

	eb_ptr->bearer->mtu = dev->mtu;

	switch (evt) {
	case NETDEV_CHANGE:
		if (netif_carrier_ok(dev))
			tipc_continue(eb_ptr->bearer);
		else
			tipc_block_bearer(eb_ptr->bearer->name);
		break;
	case NETDEV_UP:
		tipc_continue(eb_ptr->bearer);
		break;
	case NETDEV_DOWN:
		tipc_block_bearer(eb_ptr->bearer->name);
		break;
	case NETDEV_CHANGEMTU:
	case NETDEV_CHANGEADDR:
		tipc_block_bearer(eb_ptr->bearer->name);
		tipc_continue(eb_ptr->bearer);
		break;
	case NETDEV_UNREGISTER:
	case NETDEV_CHANGENAME:
		tipc_disable_bearer(eb_ptr->bearer->name);
		break;
	}
	return NOTIFY_OK;
}