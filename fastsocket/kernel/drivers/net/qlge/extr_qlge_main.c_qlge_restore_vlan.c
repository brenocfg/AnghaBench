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
struct ql_adapter {int /*<<< orphan*/  ndev; scalar_t__ vlgrp; } ;

/* Variables and functions */
 scalar_t__ VLAN_GROUP_ARRAY_LEN ; 
 int /*<<< orphan*/  qlge_vlan_rx_add_vid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qlge_vlan_rx_register (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vlan_group_get_device (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void qlge_restore_vlan(struct ql_adapter *qdev)
{
	qlge_vlan_rx_register(qdev->ndev, qdev->vlgrp);

	if (qdev->vlgrp) {
		u16 vid;
			for (vid = 0; vid < VLAN_GROUP_ARRAY_LEN; vid++) {
				if (!vlan_group_get_device(qdev->vlgrp, vid))
					continue;
				qlge_vlan_rx_add_vid(qdev->ndev, vid);
			}
	}
}