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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_lun {int dummy; } ;
struct ft_cmd {int /*<<< orphan*/ * ft_sense_buffer; TYPE_1__* sess; int /*<<< orphan*/  se_cmd; int /*<<< orphan*/  req_frame; } ;
struct fcp_cmnd {int fc_tm_flags; int /*<<< orphan*/  fc_lun; } ;
struct TYPE_2__ {int /*<<< orphan*/  se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_CMND_FIELDS_INVALID ; 
#define  FCP_TMF_ABT_TASK_SET 132 
#define  FCP_TMF_CLR_ACA 131 
#define  FCP_TMF_CLR_TASK_SET 130 
 int /*<<< orphan*/  FCP_TMF_FAILED ; 
#define  FCP_TMF_LUN_RESET 129 
#define  FCP_TMF_TGT_RESET 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TMR_ABORT_TASK_SET ; 
 int /*<<< orphan*/  TMR_CLEAR_ACA ; 
 int /*<<< orphan*/  TMR_CLEAR_TASK_SET ; 
 int /*<<< orphan*/  TMR_LUN_RESET ; 
 int /*<<< orphan*/  TMR_TARGET_WARM_RESET ; 
 struct fcp_cmnd* fc_frame_payload_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ft_send_resp_code_and_free (struct ft_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  scsilun_to_int (struct scsi_lun*) ; 
 int target_submit_tmr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ft_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ft_send_tm(struct ft_cmd *cmd)
{
	struct fcp_cmnd *fcp;
	int rc;
	u8 tm_func;

	fcp = fc_frame_payload_get(cmd->req_frame, sizeof(*fcp));

	switch (fcp->fc_tm_flags) {
	case FCP_TMF_LUN_RESET:
		tm_func = TMR_LUN_RESET;
		break;
	case FCP_TMF_TGT_RESET:
		tm_func = TMR_TARGET_WARM_RESET;
		break;
	case FCP_TMF_CLR_TASK_SET:
		tm_func = TMR_CLEAR_TASK_SET;
		break;
	case FCP_TMF_ABT_TASK_SET:
		tm_func = TMR_ABORT_TASK_SET;
		break;
	case FCP_TMF_CLR_ACA:
		tm_func = TMR_CLEAR_ACA;
		break;
	default:
		/*
		 * FCP4r01 indicates having a combination of
		 * tm_flags set is invalid.
		 */
		pr_debug("invalid FCP tm_flags %x\n", fcp->fc_tm_flags);
		ft_send_resp_code_and_free(cmd, FCP_CMND_FIELDS_INVALID);
		return;
	}

	/* FIXME: Add referenced task tag for ABORT_TASK */
	rc = target_submit_tmr(&cmd->se_cmd, cmd->sess->se_sess,
		&cmd->ft_sense_buffer[0], scsilun_to_int((struct scsi_lun *)&fcp->fc_lun),
		cmd, tm_func, GFP_KERNEL, 0, 0);
	if (rc < 0)
		ft_send_resp_code_and_free(cmd, FCP_TMF_FAILED);
}