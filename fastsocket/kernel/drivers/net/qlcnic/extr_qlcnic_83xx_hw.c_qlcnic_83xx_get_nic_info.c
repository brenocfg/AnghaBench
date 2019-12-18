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
typedef  int u32 ;
struct qlcnic_info {int op_type; int pci_func; int op_mode; int phys_port; int switch_mode; int capabilities; int max_mac_filters; int max_mtu; int max_tx_ques; int max_rx_ques; int min_tx_bw; int max_tx_bw; int max_bw_reg_offset; int max_linkspeed_reg_offset; } ;
struct TYPE_8__ {int* arg; } ;
struct TYPE_5__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_4__ rsp; TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_2__* ahw; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int pci_func; } ;

/* Variables and functions */
 int BIT_31 ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_NIC_INFO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_83xx_get_nic_info(struct qlcnic_adapter *adapter,
			     struct qlcnic_info *npar_info, u8 func_id)
{
	int err;
	u32 temp;
	u8 op = 0;
	struct qlcnic_cmd_args cmd;

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_NIC_INFO);
	if (func_id != adapter->ahw->pci_func) {
		temp = func_id << 16;
		cmd.req.arg[1] = op | BIT_31 | temp;
	} else {
		cmd.req.arg[1] = adapter->ahw->pci_func << 16;
	}
	err = qlcnic_issue_cmd(adapter, &cmd);
	if (err) {
		dev_info(&adapter->pdev->dev,
			 "Failed to get nic info %d\n", err);
		goto out;
	}

	npar_info->op_type = cmd.rsp.arg[1];
	npar_info->pci_func = cmd.rsp.arg[2] & 0xFFFF;
	npar_info->op_mode = (cmd.rsp.arg[2] & 0xFFFF0000) >> 16;
	npar_info->phys_port = cmd.rsp.arg[3] & 0xFFFF;
	npar_info->switch_mode = (cmd.rsp.arg[3] & 0xFFFF0000) >> 16;
	npar_info->capabilities = cmd.rsp.arg[4];
	npar_info->max_mac_filters = cmd.rsp.arg[5] & 0xFF;
	npar_info->max_mtu = (cmd.rsp.arg[5] & 0xFFFF0000) >> 16;
	npar_info->max_tx_ques = cmd.rsp.arg[6] & 0xFFFF;
	npar_info->max_rx_ques = (cmd.rsp.arg[6] & 0xFFFF0000) >> 16;
	npar_info->min_tx_bw = cmd.rsp.arg[7] & 0xFFFF;
	npar_info->max_tx_bw = (cmd.rsp.arg[7] & 0xFFFF0000) >> 16;
	if (cmd.rsp.arg[8] & 0x1)
		npar_info->max_bw_reg_offset = (cmd.rsp.arg[8] & 0x7FFE) >> 1;
	if (cmd.rsp.arg[8] & 0x10000) {
		temp = (cmd.rsp.arg[8] & 0x7FFE0000) >> 17;
		npar_info->max_linkspeed_reg_offset = temp;
	}

out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}