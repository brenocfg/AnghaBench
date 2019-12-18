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
struct qlcnic_sriov {int vlan_mode; } ;
struct TYPE_5__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; } ;
struct qlcnic_adapter {TYPE_1__* pdev; TYPE_3__* ahw; } ;
struct TYPE_6__ {struct qlcnic_sriov* sriov; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_BC_CMD_GET_ACL ; 
#define  QLC_GUEST_VLAN_MODE 129 
#define  QLC_PVID_MODE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_alloc_bc_mbx_args (struct qlcnic_cmd_args*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_set_guest_vlan_mode (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_set_pvid_mode (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_sriov_get_vf_acl(struct qlcnic_adapter *adapter)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	struct qlcnic_cmd_args cmd;
	int ret;

	ret = qlcnic_sriov_alloc_bc_mbx_args(&cmd, QLCNIC_BC_CMD_GET_ACL);
	if (ret)
		return ret;

	ret = qlcnic_issue_cmd(adapter, &cmd);
	if (ret) {
		dev_err(&adapter->pdev->dev, "Failed to get ACL, err=%d\n",
			ret);
	} else {
		sriov->vlan_mode = cmd.rsp.arg[1] & 0x3;
		switch (sriov->vlan_mode) {
		case QLC_GUEST_VLAN_MODE:
			ret = qlcnic_sriov_set_guest_vlan_mode(adapter, &cmd);
			break;
		case QLC_PVID_MODE:
			ret = qlcnic_sriov_set_pvid_mode(adapter, &cmd);
			break;
		}
	}

	qlcnic_free_mbx_args(&cmd);
	return ret;
}