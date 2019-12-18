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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; int /*<<< orphan*/  len; } ;
struct ocrdma_srq {TYPE_1__ rq; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct ocrdma_mqe {int dummy; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_2__ nic_info; } ;
struct ocrdma_destroy_srq {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_DELETE_SRQ ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_destroy_srq*) ; 
 struct ocrdma_destroy_srq* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (int /*<<< orphan*/ ,struct ocrdma_mqe*) ; 

int ocrdma_mbx_destroy_srq(struct ocrdma_dev *dev, struct ocrdma_srq *srq)
{
	int status = -ENOMEM;
	struct ocrdma_destroy_srq *cmd;
	struct pci_dev *pdev = dev->nic_info.pdev;
	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_SRQ, sizeof(*cmd));
	if (!cmd)
		return status;
	cmd->id = srq->id;
	status = ocrdma_mbx_cmd(srq->dev, (struct ocrdma_mqe *)cmd);
	if (srq->rq.va)
		dma_free_coherent(&pdev->dev, srq->rq.len,
				  srq->rq.va, srq->rq.pa);
	kfree(cmd);
	return status;
}