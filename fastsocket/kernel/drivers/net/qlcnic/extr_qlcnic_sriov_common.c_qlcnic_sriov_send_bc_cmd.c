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
struct qlcnic_vf_info {int /*<<< orphan*/  send_cmd_lock; struct qlcnic_bc_trans* send_cmd; int /*<<< orphan*/  state; } ;
struct qlcnic_bc_trans {int func_id; scalar_t__ cmd_id; struct qlcnic_vf_info* vf; } ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_4__ {TYPE_1__* sriov; } ;
struct TYPE_3__ {struct qlcnic_vf_info* vf_info; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int /*<<< orphan*/  QLC_BC_COMMAND ; 
 int /*<<< orphan*/  QLC_BC_VF_STATE ; 
 int __qlcnic_sriov_send_bc_msg (struct qlcnic_bc_trans*,struct qlcnic_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_clear_trans (struct qlcnic_vf_info*,struct qlcnic_bc_trans*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_func_to_index (struct qlcnic_adapter*,int) ; 
 scalar_t__ qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_sriov_send_bc_cmd(struct qlcnic_adapter *adapter,
				    struct qlcnic_bc_trans *trans, int pci_func)
{
	struct qlcnic_vf_info *vf;
	int err, index = qlcnic_sriov_func_to_index(adapter, pci_func);

	if (index < 0)
		return -EIO;

	vf = &adapter->ahw->sriov->vf_info[index];
	trans->vf = vf;
	trans->func_id = pci_func;

	if (!test_bit(QLC_BC_VF_STATE, &vf->state)) {
		if (qlcnic_sriov_pf_check(adapter))
			return -EIO;
		if (qlcnic_sriov_vf_check(adapter) &&
		    trans->cmd_id != QLCNIC_BC_CMD_CHANNEL_INIT)
			return -EIO;
	}

	mutex_lock(&vf->send_cmd_lock);
	vf->send_cmd = trans;
	err = __qlcnic_sriov_send_bc_msg(trans, vf, QLC_BC_COMMAND);
	qlcnic_sriov_clear_trans(vf, trans, QLC_BC_COMMAND);
	mutex_unlock(&vf->send_cmd_lock);
	return err;
}