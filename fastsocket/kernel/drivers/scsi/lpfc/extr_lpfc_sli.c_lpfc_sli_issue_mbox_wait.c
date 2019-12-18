#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; } ;
struct TYPE_5__ {int mbox_flag; int /*<<< orphan*/ * context1; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  int /*<<< orphan*/  MAILBOX_t ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int LPFC_MBX_WAKE ; 
 int MBX_BUSY ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int MBX_SUCCESS ; 
 int MBX_TIMEOUT ; 
 int /*<<< orphan*/  done_q ; 
 int /*<<< orphan*/  lpfc_sli4_swap_str (struct lpfc_hba*,TYPE_1__*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_wake_mbox_wait ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
lpfc_sli_issue_mbox_wait(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmboxq,
			 uint32_t timeout)
{
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(done_q);
	MAILBOX_t *mb = NULL;
	int retval;
	unsigned long flag;

	/* The caller might set context1 for extended buffer */
	if (pmboxq->context1)
		mb = (MAILBOX_t *)pmboxq->context1;

	pmboxq->mbox_flag &= ~LPFC_MBX_WAKE;
	/* setup wake call as IOCB callback */
	pmboxq->mbox_cmpl = lpfc_sli_wake_mbox_wait;
	/* setup context field to pass wait_queue pointer to wake function  */
	pmboxq->context1 = &done_q;

	/* now issue the command */
	retval = lpfc_sli_issue_mbox(phba, pmboxq, MBX_NOWAIT);
	if (retval == MBX_BUSY || retval == MBX_SUCCESS) {
		wait_event_interruptible_timeout(done_q,
				pmboxq->mbox_flag & LPFC_MBX_WAKE,
				msecs_to_jiffies(timeout * 1000));

		spin_lock_irqsave(&phba->hbalock, flag);
		/* restore the possible extended buffer for free resource */
		pmboxq->context1 = (uint8_t *)mb;
		/*
		 * if LPFC_MBX_WAKE flag is set the mailbox is completed
		 * else do not free the resources.
		 */
		if (pmboxq->mbox_flag & LPFC_MBX_WAKE) {
			retval = MBX_SUCCESS;
			lpfc_sli4_swap_str(phba, pmboxq);
		} else {
			retval = MBX_TIMEOUT;
			pmboxq->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		}
		spin_unlock_irqrestore(&phba->hbalock, flag);
	} else {
		/* restore the possible extended buffer for free resource */
		pmboxq->context1 = (uint8_t *)mb;
	}

	return retval;
}