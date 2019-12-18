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
typedef  int u32 ;
struct net_device {int features; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_SCTP_CSUM ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_set_tx_csum(struct net_device *netdev, u32 data)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	u32 feature_list;

	feature_list = (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM);
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
		feature_list |= NETIF_F_SCTP_CSUM;
		break;
	default:
		break;
	}
	if (data)
		netdev->features |= feature_list;
	else
		netdev->features &= ~feature_list;

	return 0;
}