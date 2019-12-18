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
struct net_device {int features; int vlan_features; int /*<<< orphan*/ * netdev_ops; scalar_t__ mem_end; scalar_t__ mem_start; } ;
struct bnad {scalar_t__ mmio_len; scalar_t__ mmio_start; struct net_device* netdev; } ;

/* Variables and functions */
 int NETIF_F_GRO ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_VLAN_FILTER ; 
 int NETIF_F_HW_VLAN_RX ; 
 int NETIF_F_HW_VLAN_TX ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  bnad_netdev_ops ; 
 int /*<<< orphan*/  bnad_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static void
bnad_netdev_init(struct bnad *bnad, bool using_dac)
{
	struct net_device *netdev = bnad->netdev;

	netdev->features |= NETIF_F_IPV6_CSUM;
	netdev->features |= NETIF_F_TSO;
	netdev->features |= NETIF_F_TSO6;

	netdev->features |= NETIF_F_GRO;
	pr_warning("bna: GRO enabled, using kernel stack GRO\n");

	netdev->features |= NETIF_F_SG | NETIF_F_IP_CSUM;

	if (using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->features |=
		NETIF_F_HW_VLAN_TX | NETIF_F_HW_VLAN_RX |
		NETIF_F_HW_VLAN_FILTER;

	netdev->vlan_features = netdev->features;
	netdev->mem_start = bnad->mmio_start;
	netdev->mem_end = bnad->mmio_start + bnad->mmio_len - 1;

	netdev->netdev_ops = &bnad_netdev_ops;
	bnad_set_ethtool_ops(netdev);
}