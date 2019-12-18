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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_vfta_set (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  igb_vlvf_set (struct igb_adapter*,int /*<<< orphan*/ ,int,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void igb_vlan_rx_add_vid(struct net_device *netdev, u16 vid)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	int pf_id = adapter->vfs_allocated_count;

	/* attempt to add filter to vlvf array */
	igb_vlvf_set(adapter, vid, true, pf_id);

	/* add the filter since PF can receive vlans w/o entry in vlvf */
	igb_vfta_set(hw, vid, true);
}