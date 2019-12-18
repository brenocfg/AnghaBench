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
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_F_HW_CSUM ; 
 scalar_t__ e1000_82543 ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_set_tx_csum(struct net_device *netdev, u32 data)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	if (hw->mac_type < e1000_82543) {
		if (!data)
			return -EINVAL;
		return 0;
	}

	if (data)
		netdev->features |= NETIF_F_HW_CSUM;
	else
		netdev->features &= ~NETIF_F_HW_CSUM;

	return 0;
}