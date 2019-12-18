#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ipr_ioa_cfg {struct ipr_cmnd* reset_cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_8__ {TYPE_2__ hdr; } ;
struct TYPE_7__ {TYPE_4__ ioasa; } ;
struct ipr_cmnd {scalar_t__ (* job_step_failed ) (struct ipr_cmnd*) ;scalar_t__ (* job_step ) (struct ipr_cmnd*) ;TYPE_1__* hrrq; int /*<<< orphan*/  queue; TYPE_3__ s; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  hrrq_free_q; } ;

/* Variables and functions */
 scalar_t__ IPR_IOASC_SENSE_KEY (scalar_t__) ; 
 scalar_t__ IPR_RC_JOB_CONTINUE ; 
 scalar_t__ IPR_RC_JOB_RETURN ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_reinit_ipr_cmnd (struct ipr_cmnd*) ; 
 scalar_t__ ipr_reset_cmd_failed (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct ipr_cmnd*) ; 
 scalar_t__ stub2 (struct ipr_cmnd*) ; 

__attribute__((used)) static void ipr_reset_ioa_job(struct ipr_cmnd *ipr_cmd)
{
	u32 rc, ioasc;
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	do {
		ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

		if (ioa_cfg->reset_cmd != ipr_cmd) {
			/*
			 * We are doing nested adapter resets and this is
			 * not the current reset job.
			 */
			list_add_tail(&ipr_cmd->queue,
					&ipr_cmd->hrrq->hrrq_free_q);
			return;
		}

		if (IPR_IOASC_SENSE_KEY(ioasc)) {
			rc = ipr_cmd->job_step_failed(ipr_cmd);
			if (rc == IPR_RC_JOB_RETURN)
				return;
		}

		ipr_reinit_ipr_cmnd(ipr_cmd);
		ipr_cmd->job_step_failed = ipr_reset_cmd_failed;
		rc = ipr_cmd->job_step(ipr_cmd);
	} while(rc == IPR_RC_JOB_CONTINUE);
}