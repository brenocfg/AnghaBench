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
typedef  scalar_t__ uint32_t ;
struct net_device {int dummy; } ;
struct be_adapter {int rx_csum; } ;

/* Variables and functions */
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_set_rx_csum(struct net_device *netdev, uint32_t data)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (data)
		adapter->rx_csum = true;
	else
		adapter->rx_csum = false;

	return 0;
}