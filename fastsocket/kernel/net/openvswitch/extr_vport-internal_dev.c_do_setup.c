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
struct net_device {int features; int vlan_features; int /*<<< orphan*/  dev_addr; scalar_t__ tx_queue_len; int /*<<< orphan*/  destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_HW_VLAN_TX ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  internal_dev_destructor ; 
 int /*<<< orphan*/  internal_dev_ethtool_ops ; 
 int /*<<< orphan*/  internal_dev_netdev_ops ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_setup(struct net_device *netdev)
{
	ether_setup(netdev);

	netdev->netdev_ops = &internal_dev_netdev_ops;

	netdev_extended(netdev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;
	netdev_extended(netdev)->ext_priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netdev->destructor = internal_dev_destructor;
	SET_ETHTOOL_OPS(netdev, &internal_dev_ethtool_ops);
	netdev->tx_queue_len = 0;

	netdev->features = NETIF_F_LLTX | NETIF_F_SG | NETIF_F_FRAGLIST |
			   NETIF_F_HIGHDMA | NETIF_F_HW_CSUM | NETIF_F_TSO;

	netdev->vlan_features = netdev->features;
	netdev->features |= NETIF_F_HW_VLAN_TX;
	netdev->features &= ~NETIF_F_LLTX;
	random_ether_addr(netdev->dev_addr);
}