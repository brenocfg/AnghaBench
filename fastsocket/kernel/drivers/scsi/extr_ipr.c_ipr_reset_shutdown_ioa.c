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
struct ipr_ioa_cfg {scalar_t__ dual_raid; TYPE_2__* hrrq; } ;
struct TYPE_7__ {int* cdb; int /*<<< orphan*/  request_type; } ;
struct TYPE_8__ {TYPE_3__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct TYPE_5__ {int shutdown_type; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; TYPE_4__ ioarcb; TYPE_1__ u; struct ipr_ioa_cfg* ioa_cfg; } ;
typedef  enum ipr_shutdown_type { ____Placeholder_ipr_shutdown_type } ipr_shutdown_type ;
struct TYPE_6__ {int /*<<< orphan*/  ioa_is_dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 unsigned long IPR_ABBREV_SHUTDOWN_TIMEOUT ; 
 unsigned long IPR_DUAL_IOA_ABBR_SHUTDOWN_TO ; 
 size_t IPR_INIT_HRRQ ; 
 unsigned long IPR_INTERNAL_TIMEOUT ; 
 int /*<<< orphan*/  IPR_IOA_RES_HANDLE ; 
 int IPR_IOA_SHUTDOWN ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_RQTYPE_IOACMD ; 
 int IPR_SHUTDOWN_NONE ; 
 int IPR_SHUTDOWN_NORMAL ; 
 int IPR_SHUTDOWN_PREPARE_FOR_NORMAL ; 
 unsigned long IPR_SHUTDOWN_TIMEOUT ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ipr_dual_ioa_raid ; 
 int /*<<< orphan*/  ipr_reset_alert ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_reset_ucode_download ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static int ipr_reset_shutdown_ioa(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	enum ipr_shutdown_type shutdown_type = ipr_cmd->u.shutdown_type;
	unsigned long timeout;
	int rc = IPR_RC_JOB_CONTINUE;

	ENTER;
	if (shutdown_type != IPR_SHUTDOWN_NONE &&
			!ioa_cfg->hrrq[IPR_INIT_HRRQ].ioa_is_dead) {
		ipr_cmd->ioarcb.res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
		ipr_cmd->ioarcb.cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
		ipr_cmd->ioarcb.cmd_pkt.cdb[0] = IPR_IOA_SHUTDOWN;
		ipr_cmd->ioarcb.cmd_pkt.cdb[1] = shutdown_type;

		if (shutdown_type == IPR_SHUTDOWN_NORMAL)
			timeout = IPR_SHUTDOWN_TIMEOUT;
		else if (shutdown_type == IPR_SHUTDOWN_PREPARE_FOR_NORMAL)
			timeout = IPR_INTERNAL_TIMEOUT;
		else if (ioa_cfg->dual_raid && ipr_dual_ioa_raid)
			timeout = IPR_DUAL_IOA_ABBR_SHUTDOWN_TO;
		else
			timeout = IPR_ABBREV_SHUTDOWN_TIMEOUT;

		ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout, timeout);

		rc = IPR_RC_JOB_RETURN;
		ipr_cmd->job_step = ipr_reset_ucode_download;
	} else
		ipr_cmd->job_step = ipr_reset_alert;

	LEAVE;
	return rc;
}