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
typedef  scalar_t__ u16 ;
struct igb_adapter {int /*<<< orphan*/  netdev; scalar_t__ vlgrp; } ;

/* Variables and functions */
 scalar_t__ VLAN_GROUP_ARRAY_LEN ; 
 int /*<<< orphan*/  igb_vlan_rx_add_vid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  igb_vlan_rx_register (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vlan_group_get_device (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void igb_restore_vlan(struct igb_adapter *adapter)
{
	igb_vlan_rx_register(adapter->netdev, adapter->vlgrp);

	if (adapter->vlgrp) {
		u16 vid;
		for (vid = 0; vid < VLAN_GROUP_ARRAY_LEN; vid++) {
			if (!vlan_group_get_device(adapter->vlgrp, vid))
				continue;
			igb_vlan_rx_add_vid(adapter->netdev, vid);
		}
	}
}