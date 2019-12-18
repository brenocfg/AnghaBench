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
struct lpfc_vport {int load_flag; } ;
struct lpfc_sli_ring {scalar_t__ ringno; } ;
struct TYPE_2__ {scalar_t__ ulpCommand; } ;
struct lpfc_iocbq {int iocb_flag; void* iocb_cmpl; void* fabric_iocb_cmpl; TYPE_1__ iocb; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
typedef  TYPE_1__ IOCB_t ;

/* Variables and functions */
 scalar_t__ CMD_ABORT_XRI_CN ; 
 scalar_t__ CMD_CLOSE_XRI_CN ; 
 int FC_UNLOADING ; 
 int IOCB_ERROR ; 
 int LPFC_DRIVER_ABORTED ; 
 scalar_t__ LPFC_ELS_RING ; 
 int LPFC_IO_FABRIC ; 
 void* lpfc_ignore_els_cmpl ; 
 int lpfc_sli_abort_iotag_issue (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 

int
lpfc_sli_issue_abort_iotag(struct lpfc_hba *phba, struct lpfc_sli_ring *pring,
			   struct lpfc_iocbq *cmdiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	int retval = IOCB_ERROR;
	IOCB_t *icmd = NULL;

	/*
	 * There are certain command types we don't want to abort.  And we
	 * don't want to abort commands that are already in the process of
	 * being aborted.
	 */
	icmd = &cmdiocb->iocb;
	if (icmd->ulpCommand == CMD_ABORT_XRI_CN ||
	    icmd->ulpCommand == CMD_CLOSE_XRI_CN ||
	    (cmdiocb->iocb_flag & LPFC_DRIVER_ABORTED) != 0)
		return 0;

	/*
	 * If we're unloading, don't abort iocb on the ELS ring, but change
	 * the callback so that nothing happens when it finishes.
	 */
	if ((vport->load_flag & FC_UNLOADING) &&
	    (pring->ringno == LPFC_ELS_RING)) {
		if (cmdiocb->iocb_flag & LPFC_IO_FABRIC)
			cmdiocb->fabric_iocb_cmpl = lpfc_ignore_els_cmpl;
		else
			cmdiocb->iocb_cmpl = lpfc_ignore_els_cmpl;
		goto abort_iotag_exit;
	}

	/* Now, we try to issue the abort to the cmdiocb out */
	retval = lpfc_sli_abort_iotag_issue(phba, pring, cmdiocb);

abort_iotag_exit:
	/*
	 * Caller to this routine should check for IOCB_ERROR
	 * and handle it properly.  This routine no longer removes
	 * iocb off txcmplq and call compl in case of IOCB_ERROR.
	 */
	return retval;
}