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
struct ipr_ioa_cfg {int hrrq_num; int /*<<< orphan*/  reset_wait_q; TYPE_1__* hrrq; scalar_t__ reset_retries; scalar_t__ in_reset_reload; TYPE_3__* host; } ;
struct ipr_cmnd {TYPE_2__* hrrq; int /*<<< orphan*/  queue; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  hrrq_free_q; } ;
struct TYPE_4__ {int ioa_is_dead; int /*<<< orphan*/  _lock; int /*<<< orphan*/  removing_ioa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 size_t IPR_INIT_HRRQ ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  ipr_trace ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_unblock_requests (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ipr_ioa_bringdown_done(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	int i;

	ENTER;
	if (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa) {
		ipr_trace;
		spin_unlock_irq(ioa_cfg->host->host_lock);
		scsi_unblock_requests(ioa_cfg->host);
		spin_lock_irq(ioa_cfg->host->host_lock);
	}

	ioa_cfg->in_reset_reload = 0;
	ioa_cfg->reset_retries = 0;
	for (i = 0; i < ioa_cfg->hrrq_num; i++) {
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].ioa_is_dead = 1;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	}
	wmb();

	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
	wake_up_all(&ioa_cfg->reset_wait_q);
	LEAVE;

	return IPR_RC_JOB_RETURN;
}