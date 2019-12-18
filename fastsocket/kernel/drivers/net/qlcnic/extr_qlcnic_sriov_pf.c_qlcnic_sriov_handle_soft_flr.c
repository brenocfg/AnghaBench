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
struct qlcnic_vf_info {int /*<<< orphan*/  pci_func; struct qlcnic_bc_trans* flr_trans; int /*<<< orphan*/  state; } ;
struct qlcnic_sriov {int dummy; } ;
struct qlcnic_bc_trans {int dummy; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_BC_VF_FLR ; 
 int /*<<< orphan*/  QLC_BC_VF_SOFT_FLR ; 
 int /*<<< orphan*/  QLC_BC_VF_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_process_flr ; 
 int /*<<< orphan*/  qlcnic_sriov_schedule_flr (struct qlcnic_sriov*,struct qlcnic_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_sriov_handle_soft_flr(struct qlcnic_adapter *adapter,
					 struct qlcnic_bc_trans *trans,
					 struct qlcnic_vf_info *vf)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;

	set_bit(QLC_BC_VF_FLR, &vf->state);
	clear_bit(QLC_BC_VF_STATE, &vf->state);
	set_bit(QLC_BC_VF_SOFT_FLR, &vf->state);
	vf->flr_trans = trans;
	qlcnic_sriov_schedule_flr(sriov, vf, qlcnic_sriov_pf_process_flr);
	netdev_info(adapter->netdev, "Software FLR for PCI func %d\n",
		    vf->pci_func);
}