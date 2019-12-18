#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_11__ {int sli_flag; TYPE_6__* mbox_active; } ;
struct TYPE_8__ {scalar_t__ intr_enable; } ;
struct lpfc_hba {TYPE_5__* pport; int /*<<< orphan*/  worker_thread; scalar_t__ cfg_sriov_nr_virtfn; int /*<<< orphan*/  hbalock; TYPE_4__ sli; TYPE_1__ sli4_hba; struct pci_dev* pcidev; } ;
struct TYPE_9__ {int /*<<< orphan*/  mbxStatus; } ;
struct TYPE_10__ {TYPE_2__ mb; } ;
struct TYPE_13__ {TYPE_3__ u; } ;
struct TYPE_12__ {scalar_t__ work_port_events; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int LPFC_ACTIVE_MBOX_WAIT_CNT ; 
 int LPFC_SLI_ASYNC_MBX_BLK ; 
 int LPFC_SLI_MBOX_ACTIVE ; 
 int /*<<< orphan*/  MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  __lpfc_mbox_cmpl_put (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_pci_function_reset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_disable_intr (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_queue_destroy (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_xri_exchange_busy_wait (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_hba_iocb_abort (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_stop_hba_timers (struct lpfc_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_sli4_hba_unset(struct lpfc_hba *phba)
{
	int wait_cnt = 0;
	LPFC_MBOXQ_t *mboxq;
	struct pci_dev *pdev = phba->pcidev;

	lpfc_stop_hba_timers(phba);
	phba->sli4_hba.intr_enable = 0;

	/*
	 * Gracefully wait out the potential current outstanding asynchronous
	 * mailbox command.
	 */

	/* First, block any pending async mailbox command from posted */
	spin_lock_irq(&phba->hbalock);
	phba->sli.sli_flag |= LPFC_SLI_ASYNC_MBX_BLK;
	spin_unlock_irq(&phba->hbalock);
	/* Now, trying to wait it out if we can */
	while (phba->sli.sli_flag & LPFC_SLI_MBOX_ACTIVE) {
		msleep(10);
		if (++wait_cnt > LPFC_ACTIVE_MBOX_WAIT_CNT)
			break;
	}
	/* Forcefully release the outstanding mailbox command if timed out */
	if (phba->sli.sli_flag & LPFC_SLI_MBOX_ACTIVE) {
		spin_lock_irq(&phba->hbalock);
		mboxq = phba->sli.mbox_active;
		mboxq->u.mb.mbxStatus = MBX_NOT_FINISHED;
		__lpfc_mbox_cmpl_put(phba, mboxq);
		phba->sli.sli_flag &= ~LPFC_SLI_MBOX_ACTIVE;
		phba->sli.mbox_active = NULL;
		spin_unlock_irq(&phba->hbalock);
	}

	/* Abort all iocbs associated with the hba */
	lpfc_sli_hba_iocb_abort(phba);

	/* Wait for completion of device XRI exchange busy */
	lpfc_sli4_xri_exchange_busy_wait(phba);

	/* Disable PCI subsystem interrupt */
	lpfc_sli4_disable_intr(phba);

	/* Disable SR-IOV if enabled */
	if (phba->cfg_sriov_nr_virtfn)
		pci_disable_sriov(pdev);

	/* Stop kthread signal shall trigger work_done one more time */
	kthread_stop(phba->worker_thread);

	/* Reset SLI4 HBA FCoE function */
	lpfc_pci_function_reset(phba);
	lpfc_sli4_queue_destroy(phba);

	/* Stop the SLI4 device port */
	phba->pport->work_port_events = 0;
}