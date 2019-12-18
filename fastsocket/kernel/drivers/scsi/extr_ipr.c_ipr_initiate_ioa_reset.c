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
struct ipr_ioa_cfg {scalar_t__ sdt_state; int hrrq_num; int in_ioa_bringdown; TYPE_3__* host; TYPE_2__* hrrq; int /*<<< orphan*/  reset_wait_q; scalar_t__ in_reset_reload; int /*<<< orphan*/ * reset_cmd; scalar_t__ reset_retries; TYPE_1__* pdev; } ;
typedef  enum ipr_shutdown_type { ____Placeholder_ipr_shutdown_type } ipr_shutdown_type ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {int ioa_is_dead; int /*<<< orphan*/  removing_ioa; int /*<<< orphan*/  _lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ABORT_DUMP ; 
 scalar_t__ GET_DUMP ; 
 size_t IPR_INIT_HRRQ ; 
 scalar_t__ IPR_NUM_RESET_RELOAD_RETRIES ; 
 int IPR_SHUTDOWN_NONE ; 
 scalar_t__ READ_DUMP ; 
 scalar_t__ WAIT_FOR_DUMP ; 
 int /*<<< orphan*/  _ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ipr_fail_all_ops (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_reset_shutdown_ioa ; 
 int /*<<< orphan*/  scsi_unblock_requests (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ipr_initiate_ioa_reset(struct ipr_ioa_cfg *ioa_cfg,
				   enum ipr_shutdown_type shutdown_type)
{
	int i;

	if (ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead)
		return;

	if (ioa_cfg->in_reset_reload) {
		if (ioa_cfg->sdt_state == GET_DUMP)
			ioa_cfg->sdt_state = WAIT_FOR_DUMP;
		else if (ioa_cfg->sdt_state == READ_DUMP)
			ioa_cfg->sdt_state = ABORT_DUMP;
	}

	if (ioa_cfg->reset_retries++ >= IPR_NUM_RESET_RELOAD_RETRIES) {
		dev_err(&ioa_cfg->pdev->dev,
			"IOA taken offline - error recovery failed\n");

		ioa_cfg->reset_retries = 0;
		for (i = 0; i < ioa_cfg->hrrq_num; i++) {
			spin_lock(&ioa_cfg->hrrq[i]._lock);
			ioa_cfg->hrrq[i].ioa_is_dead = 1;
			spin_unlock(&ioa_cfg->hrrq[i]._lock);
		}
		wmb();

		if (ioa_cfg->in_ioa_bringdown) {
			ioa_cfg->reset_cmd = NULL;
			ioa_cfg->in_reset_reload = 0;
			ipr_fail_all_ops(ioa_cfg);
			wake_up_all(&ioa_cfg->reset_wait_q);

			if (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa) {
				spin_unlock_irq(ioa_cfg->host->host_lock);
				scsi_unblock_requests(ioa_cfg->host);
				spin_lock_irq(ioa_cfg->host->host_lock);
			}
			return;
		} else {
			ioa_cfg->in_ioa_bringdown = 1;
			shutdown_type = IPR_SHUTDOWN_NONE;
		}
	}

	_ipr_initiate_ioa_reset(ioa_cfg, ipr_reset_shutdown_ioa,
				shutdown_type);
}