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
struct net_device {int mtu; } ;
struct atl1c_adapter {int rx_buffer_len; } ;

/* Variables and functions */
 int AT_RX_BUF_SIZE ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 int roundup (scalar_t__,int) ; 

__attribute__((used)) static void atl1c_set_rxbufsize(struct atl1c_adapter *adapter,
				struct net_device *dev)
{
	int mtu = dev->mtu;

	adapter->rx_buffer_len = mtu > AT_RX_BUF_SIZE ?
		roundup(mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN, 8) : AT_RX_BUF_SIZE;
}