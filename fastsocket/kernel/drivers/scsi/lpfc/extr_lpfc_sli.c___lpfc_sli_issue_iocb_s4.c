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
typedef  union lpfc_wqe {int dummy; } lpfc_wqe ;
typedef  size_t uint32_t ;
struct lpfc_sli_ring {int /*<<< orphan*/  txq; } ;
struct lpfc_sglq {scalar_t__ sli4_xritag; int /*<<< orphan*/  sli4_lxritag; } ;
struct TYPE_5__ {scalar_t__ ulpCommand; } ;
struct lpfc_iocbq {scalar_t__ sli4_xritag; int iocb_flag; size_t fcp_wqidx; int /*<<< orphan*/  sli4_lxritag; TYPE_2__ iocb; } ;
struct TYPE_6__ {int /*<<< orphan*/  els_wq; int /*<<< orphan*/ * fcp_wq; } ;
struct TYPE_4__ {struct lpfc_sli_ring* ring; } ;
struct lpfc_hba {TYPE_3__ sli4_hba; TYPE_1__ sli; } ;

/* Variables and functions */
 scalar_t__ CMD_ABORT_XRI_CN ; 
 scalar_t__ CMD_CLOSE_XRI_CN ; 
 int IOCB_BUSY ; 
 int IOCB_ERROR ; 
 int IOCB_SUCCESS ; 
 int LPFC_IO_FCP ; 
 int LPFC_USE_FCPWQIDX ; 
 scalar_t__ NO_XRI ; 
 size_t SLI_IOCB_RET_IOCB ; 
 struct lpfc_sglq* __lpfc_get_active_sglq (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 struct lpfc_sglq* __lpfc_sli_get_sglq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  __lpfc_sli_ringtx_put (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_sli4_bpl2sgl (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_sglq*) ; 
 scalar_t__ lpfc_sli4_iocb2wqe (struct lpfc_hba*,struct lpfc_iocbq*,union lpfc_wqe*) ; 
 scalar_t__ lpfc_sli4_wq_put (int /*<<< orphan*/ ,union lpfc_wqe*) ; 
 int /*<<< orphan*/  lpfc_sli_ringtxcmpl_put (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
__lpfc_sli_issue_iocb_s4(struct lpfc_hba *phba, uint32_t ring_number,
			 struct lpfc_iocbq *piocb, uint32_t flag)
{
	struct lpfc_sglq *sglq;
	union lpfc_wqe wqe;
	struct lpfc_sli_ring *pring = &phba->sli.ring[ring_number];

	if (piocb->sli4_xritag == NO_XRI) {
		if (piocb->iocb.ulpCommand == CMD_ABORT_XRI_CN ||
		    piocb->iocb.ulpCommand == CMD_CLOSE_XRI_CN)
			sglq = NULL;
		else {
			if (!list_empty(&pring->txq)) {
				if (!(flag & SLI_IOCB_RET_IOCB)) {
					__lpfc_sli_ringtx_put(phba,
						pring, piocb);
					return IOCB_SUCCESS;
				} else {
					return IOCB_BUSY;
				}
			} else {
				sglq = __lpfc_sli_get_sglq(phba, piocb);
				if (!sglq) {
					if (!(flag & SLI_IOCB_RET_IOCB)) {
						__lpfc_sli_ringtx_put(phba,
								pring,
								piocb);
						return IOCB_SUCCESS;
					} else
						return IOCB_BUSY;
				}
			}
		}
	} else if (piocb->iocb_flag &  LPFC_IO_FCP) {
		/* These IO's already have an XRI and a mapped sgl. */
		sglq = NULL;
	} else {
		/*
		 * This is a continuation of a commandi,(CX) so this
		 * sglq is on the active list
		 */
		sglq = __lpfc_get_active_sglq(phba, piocb->sli4_lxritag);
		if (!sglq)
			return IOCB_ERROR;
	}

	if (sglq) {
		piocb->sli4_lxritag = sglq->sli4_lxritag;
		piocb->sli4_xritag = sglq->sli4_xritag;
		if (NO_XRI == lpfc_sli4_bpl2sgl(phba, piocb, sglq))
			return IOCB_ERROR;
	}

	if (lpfc_sli4_iocb2wqe(phba, piocb, &wqe))
		return IOCB_ERROR;

	if ((piocb->iocb_flag & LPFC_IO_FCP) ||
		(piocb->iocb_flag & LPFC_USE_FCPWQIDX)) {
		if (unlikely(!phba->sli4_hba.fcp_wq))
			return IOCB_ERROR;
		if (lpfc_sli4_wq_put(phba->sli4_hba.fcp_wq[piocb->fcp_wqidx],
				     &wqe))
			return IOCB_ERROR;
	} else {
		if (unlikely(!phba->sli4_hba.els_wq))
			return IOCB_ERROR;
		if (lpfc_sli4_wq_put(phba->sli4_hba.els_wq, &wqe))
			return IOCB_ERROR;
	}
	lpfc_sli_ringtxcmpl_put(phba, pring, piocb);

	return 0;
}