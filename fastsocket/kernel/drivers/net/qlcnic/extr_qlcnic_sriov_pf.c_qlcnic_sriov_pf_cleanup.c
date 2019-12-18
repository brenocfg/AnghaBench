#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {int /*<<< orphan*/  state; TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  op_mode; int /*<<< orphan*/  pci_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MGMT_FUNC ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_ENABLE ; 
 int /*<<< orphan*/  __qlcnic_sriov_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_enable_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_cfg_eswitch (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_cfg_vlan_filtering (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_config_vport (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_del_flr_queue (struct qlcnic_adapter*) ; 

void qlcnic_sriov_pf_cleanup(struct qlcnic_adapter *adapter)
{
	u8 func = adapter->ahw->pci_func;

	if (!qlcnic_sriov_enable_check(adapter))
		return;

	qlcnic_sriov_pf_del_flr_queue(adapter);
	qlcnic_sriov_cfg_bc_intr(adapter, 0);
	qlcnic_sriov_pf_config_vport(adapter, 0, func);
	qlcnic_sriov_pf_cfg_eswitch(adapter, func, 0);
	qlcnic_sriov_pf_cfg_vlan_filtering(adapter, 0);
	__qlcnic_sriov_cleanup(adapter);
	adapter->ahw->op_mode = QLCNIC_MGMT_FUNC;
	clear_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
}