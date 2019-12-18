#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct vmxnet3_adapter {scalar_t__ vlan_grp; TYPE_3__* shared; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vfTable; } ;
struct TYPE_5__ {TYPE_1__ rxFilterConf; } ;
struct TYPE_6__ {TYPE_2__ devRead; } ;

/* Variables and functions */
 scalar_t__ VLAN_GROUP_ARRAY_LEN ; 
 int /*<<< orphan*/  VMXNET3_SET_VFTABLE_ENTRY (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlan_group_get_device (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
vmxnet3_restore_vlan(struct vmxnet3_adapter *adapter)
{
	if (adapter->vlan_grp) {
		u16 vid;
		u32 *vfTable = adapter->shared->devRead.rxFilterConf.vfTable;
		bool activeVlan = false;

		for (vid = 0; vid < VLAN_GROUP_ARRAY_LEN; vid++) {
			if (vlan_group_get_device(adapter->vlan_grp, vid)) {
				VMXNET3_SET_VFTABLE_ENTRY(vfTable, vid);
				activeVlan = true;
			}
		}
		if (activeVlan) {
			/* continue to allow untagged pkts */
			VMXNET3_SET_VFTABLE_ENTRY(vfTable, 0);
		}
	}
}