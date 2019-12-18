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
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {scalar_t__ cfg_lun_queue_depth; struct lpfc_hba* phba; } ;
struct lpfc_hba {TYPE_1__* pport; int /*<<< orphan*/  hbalock; scalar_t__ last_ramp_up_time; scalar_t__ last_rsrc_error_time; int /*<<< orphan*/  num_cmd_success; } ;
struct TYPE_2__ {scalar_t__ work_port_events; int /*<<< orphan*/  work_port_lock; } ;

/* Variables and functions */
 scalar_t__ QUEUE_RAMP_UP_INTERVAL ; 
 scalar_t__ WORKER_RAMP_UP_QUEUE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
lpfc_rampup_queue_depth(struct lpfc_vport  *vport,
			uint32_t queue_depth)
{
	unsigned long flags;
	struct lpfc_hba *phba = vport->phba;
	uint32_t evt_posted;
	atomic_inc(&phba->num_cmd_success);

	if (vport->cfg_lun_queue_depth <= queue_depth)
		return;
	spin_lock_irqsave(&phba->hbalock, flags);
	if (time_before(jiffies,
			phba->last_ramp_up_time + QUEUE_RAMP_UP_INTERVAL) ||
	    time_before(jiffies,
			phba->last_rsrc_error_time + QUEUE_RAMP_UP_INTERVAL)) {
		spin_unlock_irqrestore(&phba->hbalock, flags);
		return;
	}
	phba->last_ramp_up_time = jiffies;
	spin_unlock_irqrestore(&phba->hbalock, flags);

	spin_lock_irqsave(&phba->pport->work_port_lock, flags);
	evt_posted = phba->pport->work_port_events & WORKER_RAMP_UP_QUEUE;
	if (!evt_posted)
		phba->pport->work_port_events |= WORKER_RAMP_UP_QUEUE;
	spin_unlock_irqrestore(&phba->pport->work_port_lock, flags);

	if (!evt_posted)
		lpfc_worker_wake_up(phba);
	return;
}