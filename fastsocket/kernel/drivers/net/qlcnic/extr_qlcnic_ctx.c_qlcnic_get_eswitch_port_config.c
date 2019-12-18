#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct qlcnic_esw_func_cfg {int pci_func; int discard_tagged; int host_vlan_tag; int promisc_mode; int mac_override; int mac_anti_spoof; int offload_flags; int /*<<< orphan*/  vlan_id; } ;
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_1__* npars; } ;
struct TYPE_4__ {scalar_t__ op_mode; int physical_port; } ;
struct TYPE_3__ {int phy_port; } ;

/* Variables and functions */
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_6 ; 
 int BIT_7 ; 
 int EIO ; 
 int /*<<< orphan*/  LSW (int) ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 scalar_t__ __qlcnic_get_eswitch_port_config (struct qlcnic_adapter*,int*,int*) ; 
 int qlcnic_is_valid_nic_func (struct qlcnic_adapter*,int) ; 

int
qlcnic_get_eswitch_port_config(struct qlcnic_adapter *adapter,
			struct qlcnic_esw_func_cfg *esw_cfg)
{
	u32 arg1, arg2;
	int index;
	u8 phy_port;

	if (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC) {
		index = qlcnic_is_valid_nic_func(adapter, esw_cfg->pci_func);
		if (index < 0)
			return -EIO;
		phy_port = adapter->npars[index].phy_port;
	} else {
		phy_port = adapter->ahw->physical_port;
	}
	arg1 = phy_port;
	arg1 |= (esw_cfg->pci_func << 8);
	if (__qlcnic_get_eswitch_port_config(adapter, &arg1, &arg2))
		return -EIO;

	esw_cfg->discard_tagged = !!(arg1 & BIT_4);
	esw_cfg->host_vlan_tag = !!(arg1 & BIT_5);
	esw_cfg->promisc_mode = !!(arg1 & BIT_6);
	esw_cfg->mac_override = !!(arg1 & BIT_7);
	esw_cfg->vlan_id = LSW(arg1 >> 16);
	esw_cfg->mac_anti_spoof = (arg2 & 0x1);
	esw_cfg->offload_flags = ((arg2 >> 1) & 0x7);

	return 0;
}