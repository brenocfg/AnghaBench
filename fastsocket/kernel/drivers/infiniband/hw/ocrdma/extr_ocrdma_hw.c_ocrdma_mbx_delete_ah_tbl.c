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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocrdma_mqe {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pa; int /*<<< orphan*/ * va; } ;
struct TYPE_6__ {TYPE_2__ pbl; int /*<<< orphan*/  pa; int /*<<< orphan*/ * va; int /*<<< orphan*/  size; int /*<<< orphan*/  ahid; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_3__ av_tbl; TYPE_1__ nic_info; } ;
struct ocrdma_delete_ah_tbl {int /*<<< orphan*/  ahid; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_CMD_DELETE_AH_TBL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_delete_ah_tbl*) ; 
 struct ocrdma_delete_ah_tbl* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

__attribute__((used)) static void ocrdma_mbx_delete_ah_tbl(struct ocrdma_dev *dev)
{
	struct ocrdma_delete_ah_tbl *cmd;
	struct pci_dev *pdev = dev->nic_info.pdev;

	if (dev->av_tbl.va == NULL)
		return;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_AH_TBL, sizeof(*cmd));
	if (!cmd)
		return;
	cmd->ahid = dev->av_tbl.ahid;

	ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	dma_free_coherent(&pdev->dev, dev->av_tbl.size, dev->av_tbl.va,
			  dev->av_tbl.pa);
	dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->av_tbl.pbl.va,
			  dev->av_tbl.pbl.pa);
	kfree(cmd);
}