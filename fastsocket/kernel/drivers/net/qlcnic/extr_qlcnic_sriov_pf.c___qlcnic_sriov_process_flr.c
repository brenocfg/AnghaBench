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
struct qlcnic_vf_info {int /*<<< orphan*/ * flr_trans; int /*<<< orphan*/  state; int /*<<< orphan*/  pci_func; int /*<<< orphan*/  rcv_act; int /*<<< orphan*/  trans_work; int /*<<< orphan*/  rcv_pend; struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_BC_VF_FLR ; 
 int /*<<< orphan*/  QLC_BC_VF_SOFT_FLR ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_add_act_list_irqsave (int /*<<< orphan*/ ,struct qlcnic_vf_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_cleanup_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_del_rx_ctx (struct qlcnic_adapter*,struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  qlcnic_sriov_del_tx_ctx (struct qlcnic_adapter*,struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_config_vport (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __qlcnic_sriov_process_flr(struct qlcnic_vf_info *vf)
{
	struct qlcnic_adapter *adapter = vf->adapter;

	qlcnic_sriov_cleanup_list(&vf->rcv_pend);
	cancel_work_sync(&vf->trans_work);
	qlcnic_sriov_cleanup_list(&vf->rcv_act);

	if (test_bit(QLC_BC_VF_SOFT_FLR, &vf->state)) {
		qlcnic_sriov_del_tx_ctx(adapter, vf);
		qlcnic_sriov_del_rx_ctx(adapter, vf);
	}

	qlcnic_sriov_pf_config_vport(adapter, 0, vf->pci_func);

	clear_bit(QLC_BC_VF_FLR, &vf->state);
	if (test_bit(QLC_BC_VF_SOFT_FLR, &vf->state)) {
		qlcnic_sriov_add_act_list_irqsave(adapter->ahw->sriov, vf,
						  vf->flr_trans);
		clear_bit(QLC_BC_VF_SOFT_FLR, &vf->state);
		vf->flr_trans = NULL;
	}
}