#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_hba {int cfg_fcp_io_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_debug_dump_dat_rq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_els_cq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_els_wq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_fcp_cq (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_debug_dump_fcp_wq (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_debug_dump_hba_eq (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_debug_dump_hdr_rq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_mbx_cq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_mbx_wq (struct lpfc_hba*) ; 

void
lpfc_debug_dump_all_queues(struct lpfc_hba *phba)
{
	int fcp_wqidx;

	/*
	 * Dump Work Queues (WQs)
	 */
	lpfc_debug_dump_mbx_wq(phba);
	lpfc_debug_dump_els_wq(phba);

	for (fcp_wqidx = 0; fcp_wqidx < phba->cfg_fcp_io_channel; fcp_wqidx++)
		lpfc_debug_dump_fcp_wq(phba, fcp_wqidx);

	lpfc_debug_dump_hdr_rq(phba);
	lpfc_debug_dump_dat_rq(phba);
	/*
	 * Dump Complete Queues (CQs)
	 */
	lpfc_debug_dump_mbx_cq(phba);
	lpfc_debug_dump_els_cq(phba);

	for (fcp_wqidx = 0; fcp_wqidx < phba->cfg_fcp_io_channel; fcp_wqidx++)
		lpfc_debug_dump_fcp_cq(phba, fcp_wqidx);

	/*
	 * Dump Event Queues (EQs)
	 */
	for (fcp_wqidx = 0; fcp_wqidx < phba->cfg_fcp_io_channel; fcp_wqidx++)
		lpfc_debug_dump_hba_eq(phba, fcp_wqidx);
}