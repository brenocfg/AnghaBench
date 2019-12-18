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
struct e1000_adapter {int tso_force; struct e1000_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_F_TSO ; 
 int /*<<< orphan*/  NETIF_F_TSO6 ; 
 scalar_t__ e1000_82544 ; 
 scalar_t__ e1000_82547 ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,char*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int e1000_set_tso(struct net_device *netdev, u32 data)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	if ((hw->mac_type < e1000_82544) ||
	    (hw->mac_type == e1000_82547))
		return data ? -EINVAL : 0;

	if (data)
		netdev->features |= NETIF_F_TSO;
	else
		netdev->features &= ~NETIF_F_TSO;

	netdev->features &= ~NETIF_F_TSO6;

	e_info(probe, "TSO is %s\n", data ? "Enabled" : "Disabled");
	adapter->tso_force = true;
	return 0;
}