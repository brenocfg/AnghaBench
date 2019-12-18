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
struct net_device {int /*<<< orphan*/  destructor; int /*<<< orphan*/  features; int /*<<< orphan*/  vlan_features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  VETH_FEATURES ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  veth_dev_free ; 
 int /*<<< orphan*/  veth_ethtool_ops ; 
 int /*<<< orphan*/  veth_netdev_ops ; 

__attribute__((used)) static void veth_setup(struct net_device *dev)
{
	ether_setup(dev);

	netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;

	dev->netdev_ops = &veth_netdev_ops;
	dev->ethtool_ops = &veth_ethtool_ops;
	dev->features |= NETIF_F_LLTX;
	dev->features |= VETH_FEATURES;
	dev->vlan_features = dev->features;
	dev->destructor = veth_dev_free;
}