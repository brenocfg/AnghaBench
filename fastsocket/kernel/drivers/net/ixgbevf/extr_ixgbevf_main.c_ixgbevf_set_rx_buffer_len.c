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
typedef  int u16 ;
struct net_device {int mtu; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbevf_adapter {int num_rx_queues; TYPE_2__* rx_ring; struct net_device* netdev; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int rx_buf_len; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int IXGBEVF_RXBUFFER_10K ; 
 int IXGBEVF_RXBUFFER_2K ; 
 int IXGBEVF_RXBUFFER_4K ; 
 int IXGBEVF_RXBUFFER_8K ; 
 int MAXIMUM_ETHERNET_VLAN_SIZE ; 
 scalar_t__ VLAN_HLEN ; 
 scalar_t__ ixgbe_mac_X540_vf ; 
 int /*<<< orphan*/  ixgbevf_rlpml_set_vf (struct ixgbe_hw*,int) ; 

__attribute__((used)) static void ixgbevf_set_rx_buffer_len(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	int max_frame = netdev->mtu + ETH_HLEN + ETH_FCS_LEN;
	int i;
	u16 rx_buf_len;

	/* notify the PF of our intent to use this size of frame */
	ixgbevf_rlpml_set_vf(hw, max_frame);

	/* PF will allow an extra 4 bytes past for vlan tagged frames */
	max_frame += VLAN_HLEN;

	/*
	 * Allocate buffer sizes that fit well into 32K and
	 * take into account max frame size of 9.5K
	 */
	if ((hw->mac.type == ixgbe_mac_X540_vf) &&
	    (max_frame <= MAXIMUM_ETHERNET_VLAN_SIZE))
		rx_buf_len = MAXIMUM_ETHERNET_VLAN_SIZE;
	else if (max_frame <= IXGBEVF_RXBUFFER_2K)
		rx_buf_len = IXGBEVF_RXBUFFER_2K;
	else if (max_frame <= IXGBEVF_RXBUFFER_4K)
		rx_buf_len = IXGBEVF_RXBUFFER_4K;
	else if (max_frame <= IXGBEVF_RXBUFFER_8K)
		rx_buf_len = IXGBEVF_RXBUFFER_8K;
	else
		rx_buf_len = IXGBEVF_RXBUFFER_10K;

	for (i = 0; i < adapter->num_rx_queues; i++)
		adapter->rx_ring[i].rx_buf_len = rx_buf_len;
}