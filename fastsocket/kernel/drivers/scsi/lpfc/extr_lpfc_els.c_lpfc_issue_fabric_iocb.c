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
struct lpfc_iocbq {int /*<<< orphan*/  list; int /*<<< orphan*/  iocb_flag; int /*<<< orphan*/ * fabric_iocb_cmpl; int /*<<< orphan*/ * iocb_cmpl; TYPE_1__* vport; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  fabric_iocb_list; int /*<<< orphan*/  fabric_iocb_count; int /*<<< orphan*/  bit_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  FABRIC_COMANDS_BLOCKED ; 
 int IOCB_ERROR ; 
 int IOCB_SUCCESS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_CMD ; 
 int /*<<< orphan*/  LPFC_ELS_RING ; 
 int /*<<< orphan*/  LPFC_IO_FABRIC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lpfc_cmpl_fabric_iocb ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_iocb (struct lpfc_hba*,int /*<<< orphan*/ ,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_issue_fabric_iocb(struct lpfc_hba *phba, struct lpfc_iocbq *iocb)
{
	unsigned long iflags;
	int ready;
	int ret;

	if (atomic_read(&phba->fabric_iocb_count) > 1)
		BUG();

	spin_lock_irqsave(&phba->hbalock, iflags);
	ready = atomic_read(&phba->fabric_iocb_count) == 0 &&
		!test_bit(FABRIC_COMANDS_BLOCKED, &phba->bit_flags);

	if (ready)
		/* Increment fabric iocb count to hold the position */
		atomic_inc(&phba->fabric_iocb_count);
	spin_unlock_irqrestore(&phba->hbalock, iflags);
	if (ready) {
		iocb->fabric_iocb_cmpl = iocb->iocb_cmpl;
		iocb->iocb_cmpl = lpfc_cmpl_fabric_iocb;
		iocb->iocb_flag |= LPFC_IO_FABRIC;

		lpfc_debugfs_disc_trc(iocb->vport, LPFC_DISC_TRC_ELS_CMD,
			"Fabric sched2:   ste:x%x",
			iocb->vport->port_state, 0, 0);

		ret = lpfc_sli_issue_iocb(phba, LPFC_ELS_RING, iocb, 0);

		if (ret == IOCB_ERROR) {
			iocb->iocb_cmpl = iocb->fabric_iocb_cmpl;
			iocb->fabric_iocb_cmpl = NULL;
			iocb->iocb_flag &= ~LPFC_IO_FABRIC;
			atomic_dec(&phba->fabric_iocb_count);
		}
	} else {
		spin_lock_irqsave(&phba->hbalock, iflags);
		list_add_tail(&iocb->list, &phba->fabric_iocb_list);
		spin_unlock_irqrestore(&phba->hbalock, iflags);
		ret = IOCB_SUCCESS;
	}
	return ret;
}