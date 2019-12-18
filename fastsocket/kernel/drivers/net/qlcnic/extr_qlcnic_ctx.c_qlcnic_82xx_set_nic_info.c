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
struct qlcnic_info_le {void* max_tx_bw; void* min_tx_bw; void* max_rx_ques; void* max_tx_ques; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  capabilities; void* switch_mode; void* phys_port; void* op_mode; void* pci_func; } ;
struct qlcnic_info {int pci_func; int op_mode; int phys_port; int switch_mode; int max_tx_ques; int max_rx_ques; int min_tx_bw; int max_tx_bw; int /*<<< orphan*/  max_mac_filters; int /*<<< orphan*/  capabilities; } ;
struct TYPE_5__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_1__* ahw; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ op_mode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LSD (int /*<<< orphan*/ ) ; 
 int MSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_CMD_SET_NIC_INFO ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 int QLCNIC_RCODE_SUCCESS ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_82xx_set_nic_info(struct qlcnic_adapter *adapter,
			     struct qlcnic_info *nic)
{
	int err = -EIO;
	dma_addr_t nic_dma_t;
	void *nic_info_addr;
	struct qlcnic_cmd_args cmd;
	struct qlcnic_info_le *nic_info;
	size_t nic_size = sizeof(struct qlcnic_info_le);

	if (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		return err;

	nic_info_addr = dma_alloc_coherent(&adapter->pdev->dev, nic_size,
			&nic_dma_t, GFP_KERNEL);
	if (!nic_info_addr)
		return -ENOMEM;

	memset(nic_info_addr, 0, nic_size);
	nic_info = nic_info_addr;

	nic_info->pci_func = cpu_to_le16(nic->pci_func);
	nic_info->op_mode = cpu_to_le16(nic->op_mode);
	nic_info->phys_port = cpu_to_le16(nic->phys_port);
	nic_info->switch_mode = cpu_to_le16(nic->switch_mode);
	nic_info->capabilities = cpu_to_le32(nic->capabilities);
	nic_info->max_mac_filters = nic->max_mac_filters;
	nic_info->max_tx_ques = cpu_to_le16(nic->max_tx_ques);
	nic_info->max_rx_ques = cpu_to_le16(nic->max_rx_ques);
	nic_info->min_tx_bw = cpu_to_le16(nic->min_tx_bw);
	nic_info->max_tx_bw = cpu_to_le16(nic->max_tx_bw);

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_SET_NIC_INFO);
	cmd.req.arg[1] = MSD(nic_dma_t);
	cmd.req.arg[2] = LSD(nic_dma_t);
	cmd.req.arg[3] = ((nic->pci_func << 16) | nic_size);
	err = qlcnic_issue_cmd(adapter, &cmd);

	if (err != QLCNIC_RCODE_SUCCESS) {
		dev_err(&adapter->pdev->dev,
			"Failed to set nic info%d\n", err);
		err = -EIO;
	}

	dma_free_coherent(&adapter->pdev->dev, nic_size, nic_info_addr,
		nic_dma_t);
	qlcnic_free_mbx_args(&cmd);

	return err;
}