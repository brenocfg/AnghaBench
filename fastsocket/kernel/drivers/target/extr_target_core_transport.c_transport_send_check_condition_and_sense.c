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
typedef  unsigned char u8 ;
struct se_cmd {unsigned char* sense_buffer; int se_cmd_flags; TYPE_1__* se_tfo; int /*<<< orphan*/  scsi_sense_length; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  t_state_lock; } ;
typedef  int sense_reason_t ;
struct TYPE_2__ {int (* queue_status ) (struct se_cmd*) ;} ;

/* Variables and functions */
 unsigned char ABORTED_COMMAND ; 
 unsigned char DATA_PROTECT ; 
 unsigned char ILLEGAL_REQUEST ; 
 unsigned char NOT_READY ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int SCF_EMULATED_TASK_SENSE ; 
 int SCF_SENT_CHECK_CONDITION ; 
 size_t SPC_ADD_SENSE_LEN_OFFSET ; 
 size_t SPC_ASCQ_KEY_OFFSET ; 
 size_t SPC_ASC_KEY_OFFSET ; 
 size_t SPC_SENSE_KEY_OFFSET ; 
#define  TCM_ADDRESS_OUT_OF_RANGE 145 
#define  TCM_CHECK_CONDITION_ABORT_CMD 144 
#define  TCM_CHECK_CONDITION_NOT_READY 143 
#define  TCM_CHECK_CONDITION_UNIT_ATTENTION 142 
#define  TCM_INCORRECT_AMOUNT_OF_DATA 141 
#define  TCM_INVALID_CDB_FIELD 140 
#define  TCM_INVALID_PARAMETER_LIST 139 
#define  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE 138 
#define  TCM_NON_EXISTENT_LUN 137 
#define  TCM_NO_SENSE 136 
#define  TCM_PARAMETER_LIST_LENGTH_ERROR 135 
#define  TCM_SECTOR_COUNT_TOO_MANY 134 
#define  TCM_SERVICE_CRC_ERROR 133 
#define  TCM_SNACK_REJECTED 132 
#define  TCM_UNEXPECTED_UNSOLICITED_DATA 131 
#define  TCM_UNKNOWN_MODE_PAGE 130 
#define  TCM_UNSUPPORTED_SCSI_OPCODE 129 
#define  TCM_WRITE_PROTECTED 128 
 int /*<<< orphan*/  TRANSPORT_SENSE_BUFFER ; 
 unsigned char UNIT_ATTENTION ; 
 int /*<<< orphan*/  core_scsi3_ua_for_check_condition (struct se_cmd*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_get_sense_codes (struct se_cmd*,unsigned char*,unsigned char*) ; 

int
transport_send_check_condition_and_sense(struct se_cmd *cmd,
		sense_reason_t reason, int from_transport)
{
	unsigned char *buffer = cmd->sense_buffer;
	unsigned long flags;
	u8 asc = 0, ascq = 0;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (cmd->se_cmd_flags & SCF_SENT_CHECK_CONDITION) {
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		return 0;
	}
	cmd->se_cmd_flags |= SCF_SENT_CHECK_CONDITION;
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	if (!reason && from_transport)
		goto after_reason;

	if (!from_transport)
		cmd->se_cmd_flags |= SCF_EMULATED_TASK_SENSE;

	/*
	 * Actual SENSE DATA, see SPC-3 7.23.2  SPC_SENSE_KEY_OFFSET uses
	 * SENSE KEY values from include/scsi/scsi.h
	 */
	switch (reason) {
	case TCM_NO_SENSE:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* Not Ready */
		buffer[SPC_SENSE_KEY_OFFSET] = NOT_READY;
		/* NO ADDITIONAL SENSE INFORMATION */
		buffer[SPC_ASC_KEY_OFFSET] = 0;
		buffer[SPC_ASCQ_KEY_OFFSET] = 0;
		break;
	case TCM_NON_EXISTENT_LUN:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* LOGICAL UNIT NOT SUPPORTED */
		buffer[SPC_ASC_KEY_OFFSET] = 0x25;
		break;
	case TCM_UNSUPPORTED_SCSI_OPCODE:
	case TCM_SECTOR_COUNT_TOO_MANY:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* INVALID COMMAND OPERATION CODE */
		buffer[SPC_ASC_KEY_OFFSET] = 0x20;
		break;
	case TCM_UNKNOWN_MODE_PAGE:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* INVALID FIELD IN CDB */
		buffer[SPC_ASC_KEY_OFFSET] = 0x24;
		break;
	case TCM_CHECK_CONDITION_ABORT_CMD:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ABORTED COMMAND */
		buffer[SPC_SENSE_KEY_OFFSET] = ABORTED_COMMAND;
		/* BUS DEVICE RESET FUNCTION OCCURRED */
		buffer[SPC_ASC_KEY_OFFSET] = 0x29;
		buffer[SPC_ASCQ_KEY_OFFSET] = 0x03;
		break;
	case TCM_INCORRECT_AMOUNT_OF_DATA:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ABORTED COMMAND */
		buffer[SPC_SENSE_KEY_OFFSET] = ABORTED_COMMAND;
		/* WRITE ERROR */
		buffer[SPC_ASC_KEY_OFFSET] = 0x0c;
		/* NOT ENOUGH UNSOLICITED DATA */
		buffer[SPC_ASCQ_KEY_OFFSET] = 0x0d;
		break;
	case TCM_INVALID_CDB_FIELD:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* INVALID FIELD IN CDB */
		buffer[SPC_ASC_KEY_OFFSET] = 0x24;
		break;
	case TCM_INVALID_PARAMETER_LIST:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* INVALID FIELD IN PARAMETER LIST */
		buffer[SPC_ASC_KEY_OFFSET] = 0x26;
		break;
	case TCM_PARAMETER_LIST_LENGTH_ERROR:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* PARAMETER LIST LENGTH ERROR */
		buffer[SPC_ASC_KEY_OFFSET] = 0x1a;
		break;
	case TCM_UNEXPECTED_UNSOLICITED_DATA:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ABORTED COMMAND */
		buffer[SPC_SENSE_KEY_OFFSET] = ABORTED_COMMAND;
		/* WRITE ERROR */
		buffer[SPC_ASC_KEY_OFFSET] = 0x0c;
		/* UNEXPECTED_UNSOLICITED_DATA */
		buffer[SPC_ASCQ_KEY_OFFSET] = 0x0c;
		break;
	case TCM_SERVICE_CRC_ERROR:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ABORTED COMMAND */
		buffer[SPC_SENSE_KEY_OFFSET] = ABORTED_COMMAND;
		/* PROTOCOL SERVICE CRC ERROR */
		buffer[SPC_ASC_KEY_OFFSET] = 0x47;
		/* N/A */
		buffer[SPC_ASCQ_KEY_OFFSET] = 0x05;
		break;
	case TCM_SNACK_REJECTED:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ABORTED COMMAND */
		buffer[SPC_SENSE_KEY_OFFSET] = ABORTED_COMMAND;
		/* READ ERROR */
		buffer[SPC_ASC_KEY_OFFSET] = 0x11;
		/* FAILED RETRANSMISSION REQUEST */
		buffer[SPC_ASCQ_KEY_OFFSET] = 0x13;
		break;
	case TCM_WRITE_PROTECTED:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* DATA PROTECT */
		buffer[SPC_SENSE_KEY_OFFSET] = DATA_PROTECT;
		/* WRITE PROTECTED */
		buffer[SPC_ASC_KEY_OFFSET] = 0x27;
		break;
	case TCM_ADDRESS_OUT_OF_RANGE:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* ILLEGAL REQUEST */
		buffer[SPC_SENSE_KEY_OFFSET] = ILLEGAL_REQUEST;
		/* LOGICAL BLOCK ADDRESS OUT OF RANGE */
		buffer[SPC_ASC_KEY_OFFSET] = 0x21;
		break;
	case TCM_CHECK_CONDITION_UNIT_ATTENTION:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* UNIT ATTENTION */
		buffer[SPC_SENSE_KEY_OFFSET] = UNIT_ATTENTION;
		core_scsi3_ua_for_check_condition(cmd, &asc, &ascq);
		buffer[SPC_ASC_KEY_OFFSET] = asc;
		buffer[SPC_ASCQ_KEY_OFFSET] = ascq;
		break;
	case TCM_CHECK_CONDITION_NOT_READY:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/* Not Ready */
		buffer[SPC_SENSE_KEY_OFFSET] = NOT_READY;
		transport_get_sense_codes(cmd, &asc, &ascq);
		buffer[SPC_ASC_KEY_OFFSET] = asc;
		buffer[SPC_ASCQ_KEY_OFFSET] = ascq;
		break;
	case TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE:
	default:
		/* CURRENT ERROR */
		buffer[0] = 0x70;
		buffer[SPC_ADD_SENSE_LEN_OFFSET] = 10;
		/*
		 * Returning ILLEGAL REQUEST would cause immediate IO errors on
		 * Solaris initiators.  Returning NOT READY instead means the
		 * operations will be retried a finite number of times and we
		 * can survive intermittent errors.
		 */
		buffer[SPC_SENSE_KEY_OFFSET] = NOT_READY;
		/* LOGICAL UNIT COMMUNICATION FAILURE */
		buffer[SPC_ASC_KEY_OFFSET] = 0x08;
		break;
	}
	/*
	 * This code uses linux/include/scsi/scsi.h SAM status codes!
	 */
	cmd->scsi_status = SAM_STAT_CHECK_CONDITION;
	/*
	 * Automatically padded, this value is encoded in the fabric's
	 * data_length response PDU containing the SCSI defined sense data.
	 */
	cmd->scsi_sense_length  = TRANSPORT_SENSE_BUFFER;

after_reason:
	return cmd->se_tfo->queue_status(cmd);
}