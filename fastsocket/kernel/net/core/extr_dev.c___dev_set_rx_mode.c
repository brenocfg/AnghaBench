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
struct net_device_ops {int /*<<< orphan*/  (* ndo_set_multicast_list ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_set_rx_mode ) (struct net_device*) ;} ;
struct net_device {int flags; int uc_promisc; struct net_device_ops* netdev_ops; } ;
struct TYPE_2__ {int ext_priv_flags; } ;

/* Variables and functions */
 int IFF_NO_UNICAST_FLT ; 
 int IFF_UP ; 
 int /*<<< orphan*/  __dev_set_promiscuity (struct net_device*,int) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 scalar_t__ netdev_uc_empty (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

void __dev_set_rx_mode(struct net_device *dev)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	/* dev_open will call this function so the list will stay sane. */
	if (!(dev->flags&IFF_UP))
		return;

	if (!netif_device_present(dev))
		return;

	if (ops->ndo_set_rx_mode && !(netdev_extended(dev)->ext_priv_flags &
				      IFF_NO_UNICAST_FLT))
		ops->ndo_set_rx_mode(dev);
	else {
		/* Unicast addresses changes may only happen under the rtnl,
		 * therefore calling __dev_set_promiscuity here is safe.
		 */
		if (!netdev_uc_empty(dev) && !dev->uc_promisc) {
			__dev_set_promiscuity(dev, 1);
			dev->uc_promisc = 1;
		} else if (netdev_uc_empty(dev) && dev->uc_promisc) {
			__dev_set_promiscuity(dev, -1);
			dev->uc_promisc = 0;
		}

		if (ops->ndo_set_multicast_list)
			ops->ndo_set_multicast_list(dev);
	}
}