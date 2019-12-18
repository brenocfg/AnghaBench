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
struct net_device {int mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int api_version; TYPE_1__ mac; } ;
struct ixgbevf_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int IXGBE_MAX_JUMBO_FRAME_SIZE ; 
 int MAXIMUM_ETHERNET_VLAN_SIZE ; 
 int /*<<< orphan*/  hw_dbg (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  ixgbe_mac_X540_vf ; 
#define  ixgbe_mbox_api_11 128 
 int /*<<< orphan*/  ixgbevf_reinit_locked (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int ixgbevf_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	int max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;
	int max_possible_frame = MAXIMUM_ETHERNET_VLAN_SIZE;

	switch (adapter->hw.api_version) {
	case ixgbe_mbox_api_11:
		max_possible_frame = IXGBE_MAX_JUMBO_FRAME_SIZE;
		break;
	default:
		if (adapter->hw.mac.type == ixgbe_mac_X540_vf)
			max_possible_frame = IXGBE_MAX_JUMBO_FRAME_SIZE;
		break;
	}

	/* MTU < 68 is an error and causes problems on some kernels */
	if ((new_mtu < 68) || (max_frame > max_possible_frame))
		return -EINVAL;

	hw_dbg(&adapter->hw, "changing MTU from %d to %d\n",
	       netdev->mtu, new_mtu);
	/* must set new MTU before calling down or up */
	netdev->mtu = new_mtu;

	if (netif_running(netdev))
		ixgbevf_reinit_locked(adapter);

	return 0;
}