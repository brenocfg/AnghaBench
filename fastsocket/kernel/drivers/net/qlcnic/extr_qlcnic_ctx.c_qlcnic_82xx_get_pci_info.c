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
struct qlcnic_pci_info_le {int /*<<< orphan*/  mac; int /*<<< orphan*/  tx_max_bw; int /*<<< orphan*/  tx_min_bw; int /*<<< orphan*/  default_port; int /*<<< orphan*/  type; int /*<<< orphan*/  active; int /*<<< orphan*/  id; } ;
struct qlcnic_pci_info {int /*<<< orphan*/  mac; void* tx_max_bw; void* tx_min_bw; void* default_port; void* type; void* active; void* id; } ;
struct TYPE_4__ {size_t* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_2__* ahw; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ act_pci_func; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t LSD (int /*<<< orphan*/ ) ; 
 size_t MSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_CMD_GET_PCI_INFO ; 
 size_t QLCNIC_MAX_PCI_FUNC ; 
 int QLCNIC_RCODE_SUCCESS ; 
 void* QLCNIC_TYPE_NIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_82xx_get_pci_info(struct qlcnic_adapter *adapter,
			     struct qlcnic_pci_info *pci_info)
{
	int err = 0, i;
	struct qlcnic_cmd_args cmd;
	dma_addr_t pci_info_dma_t;
	struct qlcnic_pci_info_le *npar;
	void *pci_info_addr;
	size_t npar_size = sizeof(struct qlcnic_pci_info_le);
	size_t pci_size = npar_size * QLCNIC_MAX_PCI_FUNC;

	pci_info_addr = dma_alloc_coherent(&adapter->pdev->dev, pci_size,
			&pci_info_dma_t, GFP_KERNEL);
	if (!pci_info_addr)
		return -ENOMEM;
	memset(pci_info_addr, 0, pci_size);

	npar = pci_info_addr;
	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_GET_PCI_INFO);
	cmd.req.arg[1] = MSD(pci_info_dma_t);
	cmd.req.arg[2] = LSD(pci_info_dma_t);
	cmd.req.arg[3] = pci_size;
	err = qlcnic_issue_cmd(adapter, &cmd);

	adapter->ahw->act_pci_func = 0;
	if (err == QLCNIC_RCODE_SUCCESS) {
		for (i = 0; i < QLCNIC_MAX_PCI_FUNC; i++, npar++, pci_info++) {
			pci_info->id = le16_to_cpu(npar->id);
			pci_info->active = le16_to_cpu(npar->active);
			pci_info->type = le16_to_cpu(npar->type);
			if (pci_info->type == QLCNIC_TYPE_NIC)
				adapter->ahw->act_pci_func++;
			pci_info->default_port =
				le16_to_cpu(npar->default_port);
			pci_info->tx_min_bw =
				le16_to_cpu(npar->tx_min_bw);
			pci_info->tx_max_bw =
				le16_to_cpu(npar->tx_max_bw);
			memcpy(pci_info->mac, npar->mac, ETH_ALEN);
		}
	} else {
		dev_err(&adapter->pdev->dev,
			"Failed to get PCI Info%d\n", err);
		err = -EIO;
	}

	dma_free_coherent(&adapter->pdev->dev, pci_size, pci_info_addr,
		pci_info_dma_t);
	qlcnic_free_mbx_args(&cmd);

	return err;
}