#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {int /*<<< orphan*/  mbox_busy; } ;
struct lpfc_sli {int /*<<< orphan*/  sli_flag; TYPE_2__ slistat; } ;
struct TYPE_15__ {int /*<<< orphan*/  intr_enable; } ;
struct lpfc_hba {TYPE_5__* pport; int /*<<< orphan*/  hbalock; TYPE_1__ sli4_hba; struct lpfc_sli sli; } ;
struct TYPE_14__ {int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_18__ {int /*<<< orphan*/  mqe; TYPE_13__ mb; } ;
struct TYPE_20__ {TYPE_4__ u; TYPE_3__* vport; int /*<<< orphan*/  mcqe; } ;
struct TYPE_19__ {int /*<<< orphan*/  port_state; } ;
struct TYPE_17__ {int vpi; } ;
typedef  TYPE_6__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_MBOX ; 
 int LOG_SLI ; 
 int MBX_BUSY ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int MBX_SUCCESS ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_idiag_mbxacc_dump_issue_mbox (struct lpfc_hba*,TYPE_13__*) ; 
 int lpfc_mbox_cmd_check (struct lpfc_hba*,TYPE_6__*) ; 
 int lpfc_mbox_dev_check (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mbox_put (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  lpfc_mcqe_ext_status ; 
 int /*<<< orphan*/  lpfc_mcqe_status ; 
 int /*<<< orphan*/  lpfc_mqe_command ; 
 int /*<<< orphan*/  lpfc_mqe_status ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int lpfc_sli4_async_mbox_block (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_async_mbox_unblock (struct lpfc_hba*) ; 
 int lpfc_sli4_post_sync_mbox (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  lpfc_sli_config_mbox_opcode_get (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  lpfc_sli_config_mbox_subsys_get (struct lpfc_hba*,TYPE_6__*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
lpfc_sli_issue_mbox_s4(struct lpfc_hba *phba, LPFC_MBOXQ_t *mboxq,
		       uint32_t flag)
{
	struct lpfc_sli *psli = &phba->sli;
	unsigned long iflags;
	int rc;

	/* dump from issue mailbox command if setup */
	lpfc_idiag_mbxacc_dump_issue_mbox(phba, &mboxq->u.mb);

	rc = lpfc_mbox_dev_check(phba);
	if (unlikely(rc)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
				"(%d):2544 Mailbox command x%x (x%x/x%x) "
				"cannot issue Data: x%x x%x\n",
				mboxq->vport ? mboxq->vport->vpi : 0,
				mboxq->u.mb.mbxCommand,
				lpfc_sli_config_mbox_subsys_get(phba, mboxq),
				lpfc_sli_config_mbox_opcode_get(phba, mboxq),
				psli->sli_flag, flag);
		goto out_not_finished;
	}

	/* Detect polling mode and jump to a handler */
	if (!phba->sli4_hba.intr_enable) {
		if (flag == MBX_POLL)
			rc = lpfc_sli4_post_sync_mbox(phba, mboxq);
		else
			rc = -EIO;
		if (rc != MBX_SUCCESS)
			lpfc_printf_log(phba, KERN_WARNING, LOG_MBOX | LOG_SLI,
					"(%d):2541 Mailbox command x%x "
					"(x%x/x%x) failure: "
					"mqe_sta: x%x mcqe_sta: x%x/x%x "
					"Data: x%x x%x\n,",
					mboxq->vport ? mboxq->vport->vpi : 0,
					mboxq->u.mb.mbxCommand,
					lpfc_sli_config_mbox_subsys_get(phba,
									mboxq),
					lpfc_sli_config_mbox_opcode_get(phba,
									mboxq),
					bf_get(lpfc_mqe_status, &mboxq->u.mqe),
					bf_get(lpfc_mcqe_status, &mboxq->mcqe),
					bf_get(lpfc_mcqe_ext_status,
					       &mboxq->mcqe),
					psli->sli_flag, flag);
		return rc;
	} else if (flag == MBX_POLL) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_MBOX | LOG_SLI,
				"(%d):2542 Try to issue mailbox command "
				"x%x (x%x/x%x) synchronously ahead of async"
				"mailbox command queue: x%x x%x\n",
				mboxq->vport ? mboxq->vport->vpi : 0,
				mboxq->u.mb.mbxCommand,
				lpfc_sli_config_mbox_subsys_get(phba, mboxq),
				lpfc_sli_config_mbox_opcode_get(phba, mboxq),
				psli->sli_flag, flag);
		/* Try to block the asynchronous mailbox posting */
		rc = lpfc_sli4_async_mbox_block(phba);
		if (!rc) {
			/* Successfully blocked, now issue sync mbox cmd */
			rc = lpfc_sli4_post_sync_mbox(phba, mboxq);
			if (rc != MBX_SUCCESS)
				lpfc_printf_log(phba, KERN_WARNING,
					LOG_MBOX | LOG_SLI,
					"(%d):2597 Sync Mailbox command "
					"x%x (x%x/x%x) failure: "
					"mqe_sta: x%x mcqe_sta: x%x/x%x "
					"Data: x%x x%x\n,",
					mboxq->vport ? mboxq->vport->vpi : 0,
					mboxq->u.mb.mbxCommand,
					lpfc_sli_config_mbox_subsys_get(phba,
									mboxq),
					lpfc_sli_config_mbox_opcode_get(phba,
									mboxq),
					bf_get(lpfc_mqe_status, &mboxq->u.mqe),
					bf_get(lpfc_mcqe_status, &mboxq->mcqe),
					bf_get(lpfc_mcqe_ext_status,
					       &mboxq->mcqe),
					psli->sli_flag, flag);
			/* Unblock the async mailbox posting afterward */
			lpfc_sli4_async_mbox_unblock(phba);
		}
		return rc;
	}

	/* Now, interrupt mode asynchrous mailbox command */
	rc = lpfc_mbox_cmd_check(phba, mboxq);
	if (rc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_MBOX | LOG_SLI,
				"(%d):2543 Mailbox command x%x (x%x/x%x) "
				"cannot issue Data: x%x x%x\n",
				mboxq->vport ? mboxq->vport->vpi : 0,
				mboxq->u.mb.mbxCommand,
				lpfc_sli_config_mbox_subsys_get(phba, mboxq),
				lpfc_sli_config_mbox_opcode_get(phba, mboxq),
				psli->sli_flag, flag);
		goto out_not_finished;
	}

	/* Put the mailbox command to the driver internal FIFO */
	psli->slistat.mbox_busy++;
	spin_lock_irqsave(&phba->hbalock, iflags);
	lpfc_mbox_put(phba, mboxq);
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	lpfc_printf_log(phba, KERN_INFO, LOG_MBOX | LOG_SLI,
			"(%d):0354 Mbox cmd issue - Enqueue Data: "
			"x%x (x%x/x%x) x%x x%x x%x\n",
			mboxq->vport ? mboxq->vport->vpi : 0xffffff,
			bf_get(lpfc_mqe_command, &mboxq->u.mqe),
			lpfc_sli_config_mbox_subsys_get(phba, mboxq),
			lpfc_sli_config_mbox_opcode_get(phba, mboxq),
			phba->pport->port_state,
			psli->sli_flag, MBX_NOWAIT);
	/* Wake up worker thread to transport mailbox command from head */
	lpfc_worker_wake_up(phba);

	return MBX_BUSY;

out_not_finished:
	return MBX_NOT_FINISHED;
}