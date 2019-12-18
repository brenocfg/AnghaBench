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
struct lpfc_queue {int entry_repost; int EQ_max_eqe; int /*<<< orphan*/  EQ_no_entry; int /*<<< orphan*/  EQ_processed; int /*<<< orphan*/  EQ_badstate; } ;
struct TYPE_2__ {struct lpfc_queue** hba_eq; } ;
struct lpfc_hba {scalar_t__ link_state; scalar_t__ intr_type; int /*<<< orphan*/  hbalock; TYPE_1__ sli4_hba; } ;
struct lpfc_fcp_eq_hdl {int idx; int /*<<< orphan*/  fcp_eq_in_use; struct lpfc_hba* phba; } ;
struct lpfc_eqe {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 int /*<<< orphan*/  LPFC_QUEUE_NOARM ; 
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 scalar_t__ MSIX ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ lpfc_fcp_look_ahead ; 
 int lpfc_intr_state_check (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli4_eq_clr_intr (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_eq_flush (struct lpfc_hba*,struct lpfc_queue*) ; 
 struct lpfc_eqe* lpfc_sli4_eq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_eq_release (struct lpfc_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_hba_handle_eqe (struct lpfc_hba*,struct lpfc_eqe*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t
lpfc_sli4_hba_intr_handler(int irq, void *dev_id)
{
	struct lpfc_hba *phba;
	struct lpfc_fcp_eq_hdl *fcp_eq_hdl;
	struct lpfc_queue *fpeq;
	struct lpfc_eqe *eqe;
	unsigned long iflag;
	int ecount = 0;
	int fcp_eqidx;

	/* Get the driver's phba structure from the dev_id */
	fcp_eq_hdl = (struct lpfc_fcp_eq_hdl *)dev_id;
	phba = fcp_eq_hdl->phba;
	fcp_eqidx = fcp_eq_hdl->idx;

	if (unlikely(!phba))
		return IRQ_NONE;
	if (unlikely(!phba->sli4_hba.hba_eq))
		return IRQ_NONE;

	/* Get to the EQ struct associated with this vector */
	fpeq = phba->sli4_hba.hba_eq[fcp_eqidx];
	if (unlikely(!fpeq))
		return IRQ_NONE;

	if (lpfc_fcp_look_ahead) {
		if (atomic_dec_and_test(&fcp_eq_hdl->fcp_eq_in_use))
			lpfc_sli4_eq_clr_intr(fpeq);
		else {
			atomic_inc(&fcp_eq_hdl->fcp_eq_in_use);
			return IRQ_NONE;
		}
	}

	/* Check device state for handling interrupt */
	if (unlikely(lpfc_intr_state_check(phba))) {
		fpeq->EQ_badstate++;
		/* Check again for link_state with lock held */
		spin_lock_irqsave(&phba->hbalock, iflag);
		if (phba->link_state < LPFC_LINK_DOWN)
			/* Flush, clear interrupt, and rearm the EQ */
			lpfc_sli4_eq_flush(phba, fpeq);
		spin_unlock_irqrestore(&phba->hbalock, iflag);
		if (lpfc_fcp_look_ahead)
			atomic_inc(&fcp_eq_hdl->fcp_eq_in_use);
		return IRQ_NONE;
	}

	/*
	 * Process all the event on FCP fast-path EQ
	 */
	while ((eqe = lpfc_sli4_eq_get(fpeq))) {
		lpfc_sli4_hba_handle_eqe(phba, eqe, fcp_eqidx);
		if (!(++ecount % fpeq->entry_repost))
			lpfc_sli4_eq_release(fpeq, LPFC_QUEUE_NOARM);
		fpeq->EQ_processed++;
	}

	/* Track the max number of EQEs processed in 1 intr */
	if (ecount > fpeq->EQ_max_eqe)
		fpeq->EQ_max_eqe = ecount;

	/* Always clear and re-arm the fast-path EQ */
	lpfc_sli4_eq_release(fpeq, LPFC_QUEUE_REARM);

	if (unlikely(ecount == 0)) {
		fpeq->EQ_no_entry++;

		if (lpfc_fcp_look_ahead) {
			atomic_inc(&fcp_eq_hdl->fcp_eq_in_use);
			return IRQ_NONE;
		}

		if (phba->intr_type == MSIX)
			/* MSI-X treated interrupt served as no EQ share INT */
			lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
					"0358 MSI-X interrupt with no EQE\n");
		else
			/* Non MSI-X treated on interrupt as EQ share INT */
			return IRQ_NONE;
	}

	if (lpfc_fcp_look_ahead)
		atomic_inc(&fcp_eq_hdl->fcp_eq_in_use);
	return IRQ_HANDLED;
}