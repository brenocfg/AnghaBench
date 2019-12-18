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
typedef  size_t u32 ;
struct task_status_struct {int /*<<< orphan*/  resp; int /*<<< orphan*/  stat; } ;
struct task_abort_resp {int /*<<< orphan*/  scp; int /*<<< orphan*/  tag; int /*<<< orphan*/  status; } ;
struct sas_task {int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;int /*<<< orphan*/  task_state_lock; int /*<<< orphan*/  task_state_flags; struct task_status_struct task_status; } ;
struct pm8001_hba_info {struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {int id; } ;
struct pm8001_ccb_info {struct pm8001_device* device; struct sas_task* task; } ;

/* Variables and functions */
#define  IO_NOT_VALID 129 
#define  IO_SUCCESS 128 
 int NCQ_ABORT_ALL_FLAG ; 
 int /*<<< orphan*/  PM8001_EH_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SAS_TASK_AT_INITIATOR ; 
 int /*<<< orphan*/  SAS_TASK_COMPLETE ; 
 int /*<<< orphan*/  SAS_TASK_STATE_DONE ; 
 int /*<<< orphan*/  SAS_TASK_STATE_PENDING ; 
 int /*<<< orphan*/  TMF_RESP_FUNC_FAILED ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pm8001_ccb_task_free (struct pm8001_hba_info*,struct sas_task*,struct pm8001_ccb_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  sas_free_task (struct sas_task*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 

int pm8001_mpi_task_abort_resp(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct sas_task *t;
	struct pm8001_ccb_info *ccb;
	unsigned long flags;
	u32 status ;
	u32 tag, scp;
	struct task_status_struct *ts;
	struct pm8001_device *pm8001_dev;

	struct task_abort_resp *pPayload =
		(struct task_abort_resp *)(piomb + 4);

	status = le32_to_cpu(pPayload->status);
	tag = le32_to_cpu(pPayload->tag);
	if (!tag) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk(" TAG NULL. RETURNING !!!"));
		return -1;
	}

	scp = le32_to_cpu(pPayload->scp);
	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	pm8001_dev = ccb->device; /* retrieve device */

	if (!t)	{
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk(" TASK NULL. RETURNING !!!"));
		return -1;
	}
	ts = &t->task_status;
	if (status != 0)
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("task abort failed status 0x%x ,"
			"tag = 0x%x, scp= 0x%x\n", status, tag, scp));
	switch (status) {
	case IO_SUCCESS:
		PM8001_EH_DBG(pm8001_ha, pm8001_printk("IO_SUCCESS\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_GOOD;
		break;
	case IO_NOT_VALID:
		PM8001_EH_DBG(pm8001_ha, pm8001_printk("IO_NOT_VALID\n"));
		ts->resp = TMF_RESP_FUNC_FAILED;
		break;
	}
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	spin_unlock_irqrestore(&t->task_state_lock, flags);
	pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
	mb();

	if ((pm8001_dev->id & NCQ_ABORT_ALL_FLAG) && t)	{
		pm8001_tag_free(pm8001_ha, tag);
		sas_free_task(t);
		/* clear the flag */
		pm8001_dev->id &= 0xBFFFFFFF;
	} else
		t->task_done(t);

	return 0;
}