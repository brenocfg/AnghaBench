#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct qlcnic_vport {int spoofchk; int* mac; scalar_t__ vlan_mode; int vlan; } ;
struct TYPE_9__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_4__ req; } ;
struct qlcnic_adapter {TYPE_5__* pdev; TYPE_3__* ahw; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_2__* sriov; } ;
struct TYPE_7__ {TYPE_1__* vf_info; } ;
struct TYPE_6__ {struct qlcnic_vport* vp; } ;

/* Variables and functions */
 int BIT_1 ; 
 int BIT_3 ; 
 int BIT_6 ; 
 int BIT_8 ; 
 int /*<<< orphan*/  QLCNIC_CMD_SET_NIC_INFO ; 
 scalar_t__ QLC_PVID_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_func_to_index (struct qlcnic_adapter*,int) ; 

__attribute__((used)) static int qlcnic_sriov_set_vf_acl(struct qlcnic_adapter *adapter, u8 func)
{
	struct qlcnic_cmd_args cmd;
	struct qlcnic_vport *vp;
	int err, id;
	u8 *mac;

	id = qlcnic_sriov_func_to_index(adapter, func);
	if (id < 0)
		return id;

	vp = adapter->ahw->sriov->vf_info[id].vp;
	err = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	if (err)
		return err;

	cmd.req.arg[1] = 0x3 | func << 16;
	if (vp->spoofchk == true) {
		mac = vp->mac;
		cmd.req.arg[2] |= BIT_1 | BIT_3 | BIT_8;
		cmd.req.arg[4] = mac[5] | mac[4] << 8 | mac[3] << 16 |
				 mac[2] << 24;
		cmd.req.arg[5] = mac[1] | mac[0] << 8;
	}

	if (vp->vlan_mode == QLC_PVID_MODE) {
		cmd.req.arg[2] |= BIT_6;
		cmd.req.arg[3] |= vp->vlan << 8;
	}

	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err)
		dev_err(&adapter->pdev->dev, "Failed to set ACL, err=%d\n",
			err);

	qlcnic_free_mbx_args(&cmd);
	return err;
}