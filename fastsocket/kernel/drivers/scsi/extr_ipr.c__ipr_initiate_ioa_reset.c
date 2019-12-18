#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipr_ioa_cfg {int in_reset_reload; int hrrq_num; struct ipr_cmnd* reset_cmd; int /*<<< orphan*/  host; TYPE_1__* hrrq; } ;
struct TYPE_4__ {int shutdown_type; } ;
struct ipr_cmnd {int (* job_step ) (struct ipr_cmnd*) ;TYPE_2__ u; } ;
typedef  enum ipr_shutdown_type { ____Placeholder_ipr_shutdown_type } ipr_shutdown_type ;
struct TYPE_3__ {int /*<<< orphan*/  removing_ioa; int /*<<< orphan*/  _lock; scalar_t__ allow_cmds; } ;

/* Variables and functions */
 size_t IPR_INIT_HRRQ ; 
 struct ipr_cmnd* ipr_get_free_ipr_cmnd (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_reset_ioa_job (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void _ipr_initiate_ioa_reset(struct ipr_ioa_cfg *ioa_cfg,
				    int (*job_step) (struct ipr_cmnd *),
				    enum ipr_shutdown_type shutdown_type)
{
	struct ipr_cmnd *ipr_cmd;
	int i;

	ioa_cfg->in_reset_reload = 1;
	for (i = 0; i < ioa_cfg->hrrq_num; i++) {
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_cmds = 0;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	}
	wmb();
	if (!ioa_cfg->hrrq[IPR_INIT_HRRQ].removing_ioa)
		scsi_block_requests(ioa_cfg->host);

	ipr_cmd = ipr_get_free_ipr_cmnd(ioa_cfg);
	ioa_cfg->reset_cmd = ipr_cmd;
	ipr_cmd->job_step = job_step;
	ipr_cmd->u.shutdown_type = shutdown_type;

	ipr_reset_ioa_job(ipr_cmd);
}