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
struct qlcnic_vport {int vlan_mode; int vlan; } ;
struct qlcnic_vf_info {struct qlcnic_vport* vp; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; } ;
struct qlcnic_bc_trans {TYPE_1__* req_hdr; struct qlcnic_vf_info* vf; } ;
struct TYPE_3__ {int cmd_op; } ;

/* Variables and functions */
#define  QLC_GUEST_VLAN_MODE 129 
#define  QLC_PVID_MODE 128 

__attribute__((used)) static int qlcnic_sriov_pf_get_acl_cmd(struct qlcnic_bc_trans *trans,
				       struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info *vf = trans->vf;
	struct qlcnic_vport *vp = vf->vp;
	u8 cmd_op, mode = vp->vlan_mode;

	cmd_op = trans->req_hdr->cmd_op;
	cmd->rsp.arg[0] = (cmd_op & 0xffff) | 14 << 16 | 1 << 25;

	switch (mode) {
	case QLC_GUEST_VLAN_MODE:
		cmd->rsp.arg[1] = mode | 1 << 8;
		cmd->rsp.arg[2] = 1 << 16;
		break;
	case QLC_PVID_MODE:
		cmd->rsp.arg[1] = mode | 1 << 8 | vp->vlan << 16;
		break;
	}

	return 0;
}