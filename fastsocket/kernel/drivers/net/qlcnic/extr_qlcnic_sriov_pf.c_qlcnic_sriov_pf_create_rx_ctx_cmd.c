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
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_vf_info {scalar_t__ rx_ctx_id; int /*<<< orphan*/  pci_func; TYPE_3__* vp; struct qlcnic_adapter* adapter; } ;
struct qlcnic_rcv_mbx_out {scalar_t__ ctx_id; } ;
struct TYPE_5__ {int* arg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; } ;
struct qlcnic_bc_trans {struct qlcnic_vf_info* vf; } ;
struct qlcnic_adapter {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vlan; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cfg_vf_def_mac (struct qlcnic_adapter*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_validate_create_rx_ctx (struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_create_rx_ctx_cmd(struct qlcnic_bc_trans *tran,
					     struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info *vf = tran->vf;
	struct qlcnic_adapter *adapter = vf->adapter;
	struct qlcnic_rcv_mbx_out *mbx_out;
	int err;
	u16 vlan;

	err = qlcnic_sriov_validate_create_rx_ctx(cmd);
	if (err) {
		cmd->rsp.arg[0] |= (0x6 << 25);
		return err;
	}

	cmd->req.arg[6] = vf->vp->handle;
	err = qlcnic_issue_cmd(adapter, cmd);

	vlan = vf->vp->vlan;
	if (!err) {
		mbx_out = (struct qlcnic_rcv_mbx_out *)&cmd->rsp.arg[1];
		vf->rx_ctx_id = mbx_out->ctx_id;
		qlcnic_sriov_cfg_vf_def_mac(adapter, vf->vp, vf->pci_func,
					    vlan, QLCNIC_MAC_ADD);
	} else {
		vf->rx_ctx_id = 0;
	}

	return err;
}