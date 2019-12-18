#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lpfc_scsi_buf {scalar_t__ seg_cnt; scalar_t__ prot_seg_cnt; TYPE_2__* pCmd; } ;
struct lpfc_hba {TYPE_1__* pcidev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sc_data_direction; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dma_unmap (TYPE_2__*) ; 
 int /*<<< orphan*/  scsi_prot_sg_count (TYPE_2__*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (TYPE_2__*) ; 

__attribute__((used)) static void
lpfc_scsi_unprep_dma_buf(struct lpfc_hba *phba, struct lpfc_scsi_buf *psb)
{
	/*
	 * There are only two special cases to consider.  (1) the scsi command
	 * requested scatter-gather usage or (2) the scsi command allocated
	 * a request buffer, but did not request use_sg.  There is a third
	 * case, but it does not require resource deallocation.
	 */
	if (psb->seg_cnt > 0)
		scsi_dma_unmap(psb->pCmd);
	if (psb->prot_seg_cnt > 0)
		dma_unmap_sg(&phba->pcidev->dev, scsi_prot_sglist(psb->pCmd),
				scsi_prot_sg_count(psb->pCmd),
				psb->pCmd->sc_data_direction);
}