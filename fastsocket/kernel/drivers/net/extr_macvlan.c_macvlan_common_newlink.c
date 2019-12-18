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
struct nlattr {int dummy; } ;
struct net_device {scalar_t__ rtnl_link_ops; scalar_t__ mtu; int /*<<< orphan*/  dev_addr; struct macvlan_port* macvlan_port; } ;
struct net {int dummy; } ;
struct macvlan_port {int passthru; int /*<<< orphan*/  vlans; } ;
struct macvlan_dev {int (* receive ) (struct sk_buff*) ;int (* forward ) (struct net_device*,struct sk_buff*) ;scalar_t__ mode; int /*<<< orphan*/  list; struct macvlan_port* port; struct net_device* dev; struct net_device* lowerdev; } ;
struct TYPE_2__ {struct net* src_net; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_LINK ; 
 size_t IFLA_MACVLAN_MODE ; 
 size_t IFLA_MTU ; 
 scalar_t__ MACVLAN_MODE_PASSTHRU ; 
 scalar_t__ MACVLAN_MODE_VEPA ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int macvlan_port_create (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 
 int register_netdevice (struct net_device*) ; 

int macvlan_common_newlink(struct net_device *dev,
			   struct nlattr *tb[], struct nlattr *data[],
			   int (*receive)(struct sk_buff *skb),
			   int (*forward)(struct net_device *dev,
					  struct sk_buff *skb))
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net *src_net = netdev_extended(dev)->src_net;
	struct macvlan_port *port;
	struct net_device *lowerdev;
	int err;

	if (!tb[IFLA_LINK])
		return -EINVAL;

	lowerdev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	if (lowerdev == NULL)
		return -ENODEV;

	/* When creating macvlans on top of other macvlans - use
	 * the real device as the lowerdev.
	 */
	if (lowerdev->rtnl_link_ops == dev->rtnl_link_ops) {
		struct macvlan_dev *lowervlan = netdev_priv(lowerdev);
		lowerdev = lowervlan->lowerdev;
	}

	if (!tb[IFLA_MTU])
		dev->mtu = lowerdev->mtu;
	else if (dev->mtu > lowerdev->mtu)
		return -EINVAL;

	if (!tb[IFLA_ADDRESS])
		random_ether_addr(dev->dev_addr);

	if (lowerdev->macvlan_port == NULL) {
		err = macvlan_port_create(lowerdev);
		if (err < 0)
			return err;
	}
	port = lowerdev->macvlan_port;

	/* Only 1 macvlan device can be created in passthru mode */
	if (port->passthru)
		return -EINVAL;

	vlan->lowerdev = lowerdev;
	vlan->dev      = dev;
	vlan->port     = port;
	vlan->receive  = receive;
	vlan->forward  = forward;

	vlan->mode     = MACVLAN_MODE_VEPA;
	if (data && data[IFLA_MACVLAN_MODE])
		vlan->mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);

	if (vlan->mode == MACVLAN_MODE_PASSTHRU) {
		if (!list_empty(&port->vlans))
			return -EINVAL;
		port->passthru = true;
		memcpy(dev->dev_addr, lowerdev->dev_addr, ETH_ALEN);
	}

	err = register_netdevice(dev);
	if (err < 0)
		return err;

	list_add_tail_rcu(&vlan->list, &port->vlans);
	netif_stacked_transfer_operstate(lowerdev, dev);
	return 0;
}