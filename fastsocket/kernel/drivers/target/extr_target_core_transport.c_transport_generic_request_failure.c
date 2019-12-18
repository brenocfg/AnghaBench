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
struct se_cmd {int t_state; int transport_state; TYPE_4__* se_dev; int /*<<< orphan*/ * t_task_cdb; TYPE_3__* se_tfo; int /*<<< orphan*/  orig_fe_lun; TYPE_2__* se_sess; int /*<<< orphan*/  scsi_status; } ;
typedef  int sense_reason_t ;
struct TYPE_5__ {int emulate_ua_intlck_ctrl; } ;
struct TYPE_8__ {TYPE_1__ dev_attrib; } ;
struct TYPE_7__ {int (* get_cmd_state ) (struct se_cmd*) ;int (* queue_status ) (struct se_cmd*) ;int /*<<< orphan*/  (* get_task_tag ) (struct se_cmd*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  se_node_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_2CH_PREVIOUS_RESERVATION_CONFLICT_STATUS ; 
 int CMD_T_ACTIVE ; 
 int CMD_T_SENT ; 
 int CMD_T_STOP ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SAM_STAT_RESERVATION_CONFLICT ; 
#define  TCM_ADDRESS_OUT_OF_RANGE 141 
#define  TCM_CHECK_CONDITION_ABORT_CMD 140 
#define  TCM_CHECK_CONDITION_NOT_READY 139 
#define  TCM_CHECK_CONDITION_UNIT_ATTENTION 138 
#define  TCM_INVALID_CDB_FIELD 137 
#define  TCM_INVALID_PARAMETER_LIST 136 
#define  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE 135 
#define  TCM_NON_EXISTENT_LUN 134 
#define  TCM_OUT_OF_RESOURCES 133 
#define  TCM_PARAMETER_LIST_LENGTH_ERROR 132 
#define  TCM_RESERVATION_CONFLICT 131 
#define  TCM_UNKNOWN_MODE_PAGE 130 
#define  TCM_UNSUPPORTED_SCSI_OPCODE 129 
#define  TCM_WRITE_PROTECTED 128 
 int TRANSPORT_COMPLETE_QF_OK ; 
 int /*<<< orphan*/  core_scsi3_ua_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int stub2 (struct se_cmd*) ; 
 int stub3 (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_cmd_check_stop_to_fabric (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_complete_task_attr (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_handle_queue_full (struct se_cmd*,TYPE_4__*) ; 
 int /*<<< orphan*/  transport_lun_remove_cmd (struct se_cmd*) ; 
 int transport_send_check_condition_and_sense (struct se_cmd*,int,int /*<<< orphan*/ ) ; 

void transport_generic_request_failure(struct se_cmd *cmd,
		sense_reason_t sense_reason)
{
	int ret = 0;

	pr_debug("-----[ Storage Engine Exception for cmd: %p ITT: 0x%08x"
		" CDB: 0x%02x\n", cmd, cmd->se_tfo->get_task_tag(cmd),
		cmd->t_task_cdb[0]);
	pr_debug("-----[ i_state: %d t_state: %d sense_reason: %d\n",
		cmd->se_tfo->get_cmd_state(cmd),
		cmd->t_state, sense_reason);
	pr_debug("-----[ CMD_T_ACTIVE: %d CMD_T_STOP: %d CMD_T_SENT: %d\n",
		(cmd->transport_state & CMD_T_ACTIVE) != 0,
		(cmd->transport_state & CMD_T_STOP) != 0,
		(cmd->transport_state & CMD_T_SENT) != 0);

	/*
	 * For SAM Task Attribute emulation for failed struct se_cmd
	 */
	transport_complete_task_attr(cmd);

	switch (sense_reason) {
	case TCM_NON_EXISTENT_LUN:
	case TCM_UNSUPPORTED_SCSI_OPCODE:
	case TCM_INVALID_CDB_FIELD:
	case TCM_INVALID_PARAMETER_LIST:
	case TCM_PARAMETER_LIST_LENGTH_ERROR:
	case TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE:
	case TCM_UNKNOWN_MODE_PAGE:
	case TCM_WRITE_PROTECTED:
	case TCM_ADDRESS_OUT_OF_RANGE:
	case TCM_CHECK_CONDITION_ABORT_CMD:
	case TCM_CHECK_CONDITION_UNIT_ATTENTION:
	case TCM_CHECK_CONDITION_NOT_READY:
		break;
	case TCM_OUT_OF_RESOURCES:
		sense_reason = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		break;
	case TCM_RESERVATION_CONFLICT:
		/*
		 * No SENSE Data payload for this case, set SCSI Status
		 * and queue the response to $FABRIC_MOD.
		 *
		 * Uses linux/include/scsi/scsi.h SAM status codes defs
		 */
		cmd->scsi_status = SAM_STAT_RESERVATION_CONFLICT;
		/*
		 * For UA Interlock Code 11b, a RESERVATION CONFLICT will
		 * establish a UNIT ATTENTION with PREVIOUS RESERVATION
		 * CONFLICT STATUS.
		 *
		 * See spc4r17, section 7.4.6 Control Mode Page, Table 349
		 */
		if (cmd->se_sess &&
		    cmd->se_dev->dev_attrib.emulate_ua_intlck_ctrl == 2)
			core_scsi3_ua_allocate(cmd->se_sess->se_node_acl,
				cmd->orig_fe_lun, 0x2C,
				ASCQ_2CH_PREVIOUS_RESERVATION_CONFLICT_STATUS);

		ret = cmd->se_tfo->queue_status(cmd);
		if (ret == -EAGAIN || ret == -ENOMEM)
			goto queue_full;
		goto check_stop;
	default:
		pr_err("Unknown transport error for CDB 0x%02x: %d\n",
			cmd->t_task_cdb[0], sense_reason);
		sense_reason = TCM_UNSUPPORTED_SCSI_OPCODE;
		break;
	}

	ret = transport_send_check_condition_and_sense(cmd, sense_reason, 0);
	if (ret == -EAGAIN || ret == -ENOMEM)
		goto queue_full;

check_stop:
	transport_lun_remove_cmd(cmd);
	if (!transport_cmd_check_stop_to_fabric(cmd))
		;
	return;

queue_full:
	cmd->t_state = TRANSPORT_COMPLETE_QF_OK;
	transport_handle_queue_full(cmd, cmd->se_dev);
}