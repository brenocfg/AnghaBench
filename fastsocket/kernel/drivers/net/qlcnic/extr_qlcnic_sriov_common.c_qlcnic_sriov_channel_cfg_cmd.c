#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_4__ rsp; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_2__* ahw; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__* sriov; } ;
struct TYPE_5__ {struct qlcnic_vf_info* vf_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int /*<<< orphan*/  QLC_BC_VF_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 scalar_t__ qlcnic_sriov_alloc_bc_mbx_args (struct qlcnic_cmd_args*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qlcnic_sriov_channel_cfg_cmd(struct qlcnic_adapter *adapter, u8 cmd_op)
{
	struct qlcnic_cmd_args cmd;
	struct qlcnic_vf_info *vf = &adapter->ahw->sriov->vf_info[0];
	int ret;

	if (qlcnic_sriov_alloc_bc_mbx_args(&cmd, cmd_op))
		return -ENOMEM;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	if (ret) {
		dev_err(&adapter->pdev->dev,
			"Failed bc channel %s %d\n", cmd_op ? "term" : "init",
			ret);
		goto out;
	}

	cmd_op = (cmd.rsp.arg[0] & 0xff);
	if (cmd.rsp.arg[0] >> 25 == 2)
		return 2;
	if (cmd_op == QLCNIC_BC_CMD_CHANNEL_INIT)
		set_bit(QLC_BC_VF_STATE, &vf->state);
	else
		clear_bit(QLC_BC_VF_STATE, &vf->state);

out:
	qlcnic_free_mbx_args(&cmd);
	return ret;
}