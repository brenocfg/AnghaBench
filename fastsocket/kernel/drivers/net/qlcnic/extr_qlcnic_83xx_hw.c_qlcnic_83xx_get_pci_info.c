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
typedef  void* u32 ;
struct qlcnic_pci_info {int id; int active; int type; int tx_min_bw; int /*<<< orphan*/  mac; void* tx_max_bw; void* default_port; } ;
struct qlcnic_hardware_context {int max_pci_func; scalar_t__ op_mode; int /*<<< orphan*/  act_pci_func; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; } ;
struct qlcnic_adapter {TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_PCI_INFO ; 
 int QLCNIC_MAX_PCI_FUNC ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int QLCNIC_TYPE_NIC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_83xx_get_pci_info(struct qlcnic_adapter *adapter,
			     struct qlcnic_pci_info *pci_info)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct device *dev = &adapter->pdev->dev;
	struct qlcnic_cmd_args cmd;
	int i, err = 0, j = 0;
	u32 temp;

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_PCI_INFO);
	err = qlcnic_issue_cmd(adapter, &cmd);

	ahw->act_pci_func = 0;
	if (err == QLCNIC_RCODE_SUCCESS) {
		ahw->max_pci_func = cmd.rsp.arg[1] & 0xFF;
		for (i = 2, j = 0; j < QLCNIC_MAX_PCI_FUNC; j++, pci_info++) {
			pci_info->id = cmd.rsp.arg[i] & 0xFFFF;
			pci_info->active = (cmd.rsp.arg[i] & 0xFFFF0000) >> 16;
			i++;
			pci_info->type = cmd.rsp.arg[i] & 0xFFFF;
			if (pci_info->type == QLCNIC_TYPE_NIC)
				ahw->act_pci_func++;
			temp = (cmd.rsp.arg[i] & 0xFFFF0000) >> 16;
			pci_info->default_port = temp;
			i++;
			pci_info->tx_min_bw = cmd.rsp.arg[i] & 0xFFFF;
			temp = (cmd.rsp.arg[i] & 0xFFFF0000) >> 16;
			pci_info->tx_max_bw = temp;
			i = i + 2;
			memcpy(pci_info->mac, &cmd.rsp.arg[i], ETH_ALEN - 2);
			i++;
			memcpy(pci_info->mac + sizeof(u32), &cmd.rsp.arg[i], 2);
			i = i + 3;
			if (ahw->op_mode == QLCNIC_MGMT_FUNC)
				dev_info(dev, "id = %d active = %d type = %d\n"
					 "\tport = %d min bw = %d max bw = %d\n"
					 "\tmac_addr =  %pM\n", pci_info->id,
					 pci_info->active, pci_info->type,
					 pci_info->default_port,
					 pci_info->tx_min_bw,
					 pci_info->tx_max_bw, pci_info->mac);
		}
		if (ahw->op_mode == QLCNIC_MGMT_FUNC)
			dev_info(dev, "Max vNIC functions = %d, active vNIC functions = %d\n",
				 ahw->max_pci_func, ahw->act_pci_func);

	} else {
		dev_err(dev, "Failed to get PCI Info, error = %d\n", err);
		err = -EIO;
	}

	qlcnic_free_mbx_args(&cmd);

	return err;
}