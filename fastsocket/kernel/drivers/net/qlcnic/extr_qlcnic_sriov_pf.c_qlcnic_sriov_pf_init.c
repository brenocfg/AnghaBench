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
typedef  scalar_t__ u8 ;
struct qlcnic_info {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  switch_mode; scalar_t__ phys_port; } ;
struct qlcnic_hardware_context {int /*<<< orphan*/  nic_mode; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  switch_mode; scalar_t__ physical_port; scalar_t__ pci_func; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_83XX_SRIOV_MODE ; 
 int qlcnic_get_nic_info (struct qlcnic_adapter*,struct qlcnic_info*,scalar_t__) ; 
 int qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_sriov_enable_check (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_get_pf_info (struct qlcnic_adapter*,struct qlcnic_info*) ; 
 int qlcnic_sriov_pf_cal_res_limit (struct qlcnic_adapter*,struct qlcnic_info*,scalar_t__) ; 
 int qlcnic_sriov_pf_cfg_eswitch (struct qlcnic_adapter*,scalar_t__,int) ; 
 int qlcnic_sriov_pf_cfg_vlan_filtering (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_pf_config_vport (struct qlcnic_adapter*,int,scalar_t__) ; 

__attribute__((used)) static int qlcnic_sriov_pf_init(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_info nic_info, pf_info, vp_info;
	int err;
	u8 func = ahw->pci_func;

	if (!qlcnic_sriov_enable_check(adapter))
		return 0;

	err = qlcnic_sriov_pf_cfg_vlan_filtering(adapter, 1);
	if (err)
		return err;

	err = qlcnic_sriov_pf_cfg_eswitch(adapter, func, 1);
	if (err)
		goto disable_vlan_filtering;

	err = qlcnic_sriov_pf_config_vport(adapter, 1, func);
	if (err)
		goto disable_eswitch;

	err = qlcnic_sriov_get_pf_info(adapter, &pf_info);
	if (err)
		goto delete_vport;

	err = qlcnic_get_nic_info(adapter, &nic_info, func);
	if (err)
		goto delete_vport;

	err = qlcnic_sriov_pf_cal_res_limit(adapter, &vp_info, func);
	if (err)
		goto delete_vport;

	err = qlcnic_sriov_cfg_bc_intr(adapter, 1);
	if (err)
		goto delete_vport;

	ahw->physical_port = (u8) nic_info.phys_port;
	ahw->switch_mode = nic_info.switch_mode;
	ahw->max_mtu = nic_info.max_mtu;
	ahw->capabilities = nic_info.capabilities;
	ahw->nic_mode = QLC_83XX_SRIOV_MODE;
	return err;

delete_vport:
	qlcnic_sriov_pf_config_vport(adapter, 0, func);

disable_eswitch:
	qlcnic_sriov_pf_cfg_eswitch(adapter, func, 0);

disable_vlan_filtering:
	qlcnic_sriov_pf_cfg_vlan_filtering(adapter, 0);

	return err;
}