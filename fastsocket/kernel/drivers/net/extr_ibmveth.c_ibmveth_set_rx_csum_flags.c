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
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  features; } ;
struct ibmveth_adapter {int rx_csum; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ibmveth_set_rx_csum_flags(struct net_device *dev, u32 data)
{
	struct ibmveth_adapter *adapter = netdev_priv(dev);

	if (data) {
		adapter->rx_csum = 1;
	} else {
		/*
		 * Since the ibmveth firmware interface does not have the
		 * concept of separate tx/rx checksum offload enable, if rx
		 * checksum is disabled we also have to disable tx checksum
		 * offload. Once we disable rx checksum offload, we are no
		 * longer allowed to send tx buffers that are not properly
		 * checksummed.
		 */
		adapter->rx_csum = 0;
		dev->features &= ~NETIF_F_IP_CSUM;
		dev->features &= ~NETIF_F_IPV6_CSUM;
	}
}