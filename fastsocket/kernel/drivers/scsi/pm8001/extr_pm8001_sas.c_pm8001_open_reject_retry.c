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
typedef  int u32 ;
struct task_status_struct {int /*<<< orphan*/  open_rej_reason; int /*<<< orphan*/  stat; int /*<<< orphan*/  resp; } ;
struct sas_task {int task_state_flags; int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;int /*<<< orphan*/  task_state_lock; struct task_status_struct task_status; } ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  devices; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {scalar_t__ dev_type; int /*<<< orphan*/  running_req; } ;
struct pm8001_ccb_info {int ccb_tag; struct sas_task* task; struct pm8001_device* device; } ;

/* Variables and functions */
 int PM8001_MAX_CCB ; 
 uintptr_t PM8001_MAX_DEVICES ; 
 int /*<<< orphan*/  SAS_OPEN_REJECT ; 
 int /*<<< orphan*/  SAS_OREJ_RSVD_RETRY ; 
 scalar_t__ SAS_PHY_UNUSED ; 
 int SAS_TASK_AT_INITIATOR ; 
 int /*<<< orphan*/  SAS_TASK_COMPLETE ; 
 int SAS_TASK_STATE_ABORTED ; 
 int SAS_TASK_STATE_DONE ; 
 int SAS_TASK_STATE_PENDING ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pm8001_ccb_task_free (struct pm8001_hba_info*,struct sas_task*,struct pm8001_ccb_info*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 
 scalar_t__ unlikely (int) ; 

void pm8001_open_reject_retry(
	struct pm8001_hba_info *pm8001_ha,
	struct sas_task *task_to_close,
	struct pm8001_device *device_to_close)
{
	int i;
	unsigned long flags;

	if (pm8001_ha == NULL)
		return;

	spin_lock_irqsave(&pm8001_ha->lock, flags);

	for (i = 0; i < PM8001_MAX_CCB; i++) {
		struct sas_task *task;
		struct task_status_struct *ts;
		struct pm8001_device *pm8001_dev;
		unsigned long flags1;
		u32 tag;
		struct pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[i];

		pm8001_dev = ccb->device;
		if (!pm8001_dev || (pm8001_dev->dev_type == SAS_PHY_UNUSED))
			continue;
		if (!device_to_close) {
			uintptr_t d = (uintptr_t)pm8001_dev
					- (uintptr_t)&pm8001_ha->devices;
			if (((d % sizeof(*pm8001_dev)) != 0)
			 || ((d / sizeof(*pm8001_dev)) >= PM8001_MAX_DEVICES))
				continue;
		} else if (pm8001_dev != device_to_close)
			continue;
		tag = ccb->ccb_tag;
		if (!tag || (tag == 0xFFFFFFFF))
			continue;
		task = ccb->task;
		if (!task || !task->task_done)
			continue;
		if (task_to_close && (task != task_to_close))
			continue;
		ts = &task->task_status;
		ts->resp = SAS_TASK_COMPLETE;
		/* Force the midlayer to retry */
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		spin_lock_irqsave(&task->task_state_lock, flags1);
		task->task_state_flags &= ~SAS_TASK_STATE_PENDING;
		task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
		task->task_state_flags |= SAS_TASK_STATE_DONE;
		if (unlikely((task->task_state_flags
				& SAS_TASK_STATE_ABORTED))) {
			spin_unlock_irqrestore(&task->task_state_lock,
				flags1);
			pm8001_ccb_task_free(pm8001_ha, task, ccb, tag);
		} else {
			spin_unlock_irqrestore(&task->task_state_lock,
				flags1);
			pm8001_ccb_task_free(pm8001_ha, task, ccb, tag);
			mb();/* in order to force CPU ordering */
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			task->task_done(task);
			spin_lock_irqsave(&pm8001_ha->lock, flags);
		}
	}

	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
}