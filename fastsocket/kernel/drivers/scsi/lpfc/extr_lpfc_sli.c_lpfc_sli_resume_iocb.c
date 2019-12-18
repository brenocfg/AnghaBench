#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpfc_sli_ring {scalar_t__ ringno; int /*<<< orphan*/  txq; } ;
struct lpfc_iocbq {int dummy; } ;
struct TYPE_2__ {scalar_t__ fcp_ring; int sli_flag; } ;
struct lpfc_hba {TYPE_1__ sli; } ;
typedef  int /*<<< orphan*/  IOCB_t ;

/* Variables and functions */
 int LPFC_PROCESS_LA ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_is_link_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/ * lpfc_sli_next_iocb_slot (struct lpfc_hba*,struct lpfc_sli_ring*) ; 
 struct lpfc_iocbq* lpfc_sli_ringtx_get (struct lpfc_hba*,struct lpfc_sli_ring*) ; 
 int /*<<< orphan*/  lpfc_sli_submit_iocb (struct lpfc_hba*,struct lpfc_sli_ring*,int /*<<< orphan*/ *,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_sli_update_full_ring (struct lpfc_hba*,struct lpfc_sli_ring*) ; 
 int /*<<< orphan*/  lpfc_sli_update_ring (struct lpfc_hba*,struct lpfc_sli_ring*) ; 

__attribute__((used)) static void
lpfc_sli_resume_iocb(struct lpfc_hba *phba, struct lpfc_sli_ring *pring)
{
	IOCB_t *iocb;
	struct lpfc_iocbq *nextiocb;

	/*
	 * Check to see if:
	 *  (a) there is anything on the txq to send
	 *  (b) link is up
	 *  (c) link attention events can be processed (fcp ring only)
	 *  (d) IOCB processing is not blocked by the outstanding mbox command.
	 */

	if (lpfc_is_link_up(phba) &&
	    (!list_empty(&pring->txq)) &&
	    (pring->ringno != phba->sli.fcp_ring ||
	     phba->sli.sli_flag & LPFC_PROCESS_LA)) {

		while ((iocb = lpfc_sli_next_iocb_slot(phba, pring)) &&
		       (nextiocb = lpfc_sli_ringtx_get(phba, pring)))
			lpfc_sli_submit_iocb(phba, pring, iocb, nextiocb);

		if (iocb)
			lpfc_sli_update_ring(phba, pring);
		else
			lpfc_sli_update_full_ring(phba, pring);
	}

	return;
}