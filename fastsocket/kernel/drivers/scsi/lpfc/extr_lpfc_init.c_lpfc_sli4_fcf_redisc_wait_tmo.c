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
struct TYPE_2__ {int fcf_flag; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;

/* Variables and functions */
 int FCF_REDISC_EVT ; 
 int FCF_REDISC_PEND ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_FIP ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_fcf_redisc_wait_tmo(unsigned long ptr)
{
	struct lpfc_hba *phba = (struct lpfc_hba *)ptr;

	/* Don't send FCF rediscovery event if timer cancelled */
	spin_lock_irq(&phba->hbalock);
	if (!(phba->fcf.fcf_flag & FCF_REDISC_PEND)) {
		spin_unlock_irq(&phba->hbalock);
		return;
	}
	/* Clear FCF rediscovery timer pending flag */
	phba->fcf.fcf_flag &= ~FCF_REDISC_PEND;
	/* FCF rediscovery event to worker thread */
	phba->fcf.fcf_flag |= FCF_REDISC_EVT;
	spin_unlock_irq(&phba->hbalock);
	lpfc_printf_log(phba, KERN_INFO, LOG_FIP,
			"2776 FCF rediscover quiescent timer expired\n");
	/* wake up worker thread */
	lpfc_worker_wake_up(phba);
}