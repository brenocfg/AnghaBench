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
struct net_device {int dummy; } ;
struct ibmveth_adapter {scalar_t__ rx_csum; } ;

/* Variables and functions */
 int ibmveth_set_csum_offload (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmveth_set_rx_csum_flags ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ibmveth_set_rx_csum(struct net_device *dev, u32 data)
{
	struct ibmveth_adapter *adapter = netdev_priv(dev);

	if ((data && adapter->rx_csum) || (!data && !adapter->rx_csum))
		return 0;

	return ibmveth_set_csum_offload(dev, data, ibmveth_set_rx_csum_flags);
}