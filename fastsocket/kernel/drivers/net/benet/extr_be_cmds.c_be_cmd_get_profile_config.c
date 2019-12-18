#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct be_resources {int /*<<< orphan*/  max_vfs; } ;
struct be_queue_info {int /*<<< orphan*/  created; } ;
struct be_pcie_res_desc {int /*<<< orphan*/  num_vfs; } ;
struct be_nic_res_desc {int dummy; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; struct be_cmd_resp_get_profile_config* va; } ;
struct be_cmd_resp_get_profile_config {int /*<<< orphan*/  func_param; int /*<<< orphan*/  desc_count; } ;
struct TYPE_4__ {struct be_queue_info q; } ;
struct be_adapter {TYPE_2__* pdev; TYPE_1__ mcc_obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int be_cmd_get_profile_config_mbox (struct be_adapter*,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int be_cmd_get_profile_config_mccq (struct be_adapter*,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int /*<<< orphan*/  be_copy_nic_desc (struct be_resources*,struct be_nic_res_desc*) ; 
 struct be_nic_res_desc* be_get_nic_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct be_pcie_res_desc* be_get_pcie_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 
 struct be_cmd_resp_get_profile_config* pci_alloc_consistent (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (TYPE_2__*,int,struct be_cmd_resp_get_profile_config*,int /*<<< orphan*/ ) ; 

int be_cmd_get_profile_config(struct be_adapter *adapter,
			      struct be_resources *res, u8 domain)
{
	struct be_cmd_resp_get_profile_config *resp;
	struct be_pcie_res_desc *pcie;
	struct be_nic_res_desc *nic;
	struct be_queue_info *mccq = &adapter->mcc_obj.q;
	struct be_dma_mem cmd;
	u32 desc_count;
	int status;

	memset(&cmd, 0, sizeof(struct be_dma_mem));
	cmd.size = sizeof(struct be_cmd_resp_get_profile_config);
	cmd.va = pci_alloc_consistent(adapter->pdev, cmd.size, &cmd.dma);
	if (!cmd.va)
		return -ENOMEM;

	if (!mccq->created)
		status = be_cmd_get_profile_config_mbox(adapter, domain, &cmd);
	else
		status = be_cmd_get_profile_config_mccq(adapter, domain, &cmd);
	if (status)
		goto err;

	resp = cmd.va;
	desc_count = le32_to_cpu(resp->desc_count);

	pcie =  be_get_pcie_desc(adapter->pdev->devfn, resp->func_param,
				 desc_count);
	if (pcie)
		res->max_vfs = le16_to_cpu(pcie->num_vfs);

	nic = be_get_nic_desc(resp->func_param, desc_count);
	if (nic)
		be_copy_nic_desc(res, nic);

err:
	if (cmd.va)
		pci_free_consistent(adapter->pdev, cmd.size, cmd.va, cmd.dma);
	return status;
}