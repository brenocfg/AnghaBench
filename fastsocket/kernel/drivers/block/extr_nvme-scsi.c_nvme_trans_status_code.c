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
typedef  int /*<<< orphan*/  u8 ;
struct sg_io_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORTED_COMMAND ; 
 int /*<<< orphan*/  HARDWARE_ERROR ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  MEDIUM_ERROR ; 
 int /*<<< orphan*/  MISCOMPARE ; 
 int /*<<< orphan*/  NOT_READY ; 
 int /*<<< orphan*/  NO_SENSE ; 
#define  NVME_SC_ABORT_LIMIT 162 
#define  NVME_SC_ABORT_MISSING 161 
#define  NVME_SC_ABORT_QUEUE 160 
#define  NVME_SC_ABORT_REQ 159 
#define  NVME_SC_ACCESS_DENIED 158 
#define  NVME_SC_APPTAG_CHECK 157 
#define  NVME_SC_ASYNC_LIMIT 156 
#define  NVME_SC_BAD_ATTRIBUTES 155 
#define  NVME_SC_CAP_EXCEEDED 154 
#define  NVME_SC_CMDID_CONFLICT 153 
#define  NVME_SC_CMD_SEQ_ERROR 152 
#define  NVME_SC_COMPARE_FAILED 151 
#define  NVME_SC_CQ_INVALID 150 
#define  NVME_SC_DATA_XFER_ERROR 149 
#define  NVME_SC_FIRMWARE_IMAGE 148 
#define  NVME_SC_FIRMWARE_SLOT 147 
#define  NVME_SC_FUSED_FAIL 146 
#define  NVME_SC_FUSED_MISSING 145 
#define  NVME_SC_GUARD_CHECK 144 
#define  NVME_SC_INTERNAL 143 
#define  NVME_SC_INVALID_FIELD 142 
#define  NVME_SC_INVALID_FORMAT 141 
#define  NVME_SC_INVALID_LOG_PAGE 140 
#define  NVME_SC_INVALID_NS 139 
#define  NVME_SC_INVALID_OPCODE 138 
#define  NVME_SC_INVALID_VECTOR 137 
#define  NVME_SC_LBA_RANGE 136 
#define  NVME_SC_NS_NOT_READY 135 
#define  NVME_SC_POWER_LOSS 134 
#define  NVME_SC_QID_INVALID 133 
#define  NVME_SC_QUEUE_SIZE 132 
#define  NVME_SC_READ_ERROR 131 
#define  NVME_SC_REFTAG_CHECK 130 
#define  NVME_SC_SUCCESS 129 
#define  NVME_SC_WRITE_FAULT 128 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  SAM_STAT_TASK_ABORTED ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASCQ_FORMAT_COMMAND_FAILED ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_LUN_ID ; 
 int /*<<< orphan*/  SCSI_ASCQ_LOG_BLOCK_APPTAG_CHECK_FAILED ; 
 int /*<<< orphan*/  SCSI_ASCQ_LOG_BLOCK_GUARD_CHECK_FAILED ; 
 int /*<<< orphan*/  SCSI_ASCQ_LOG_BLOCK_REFTAG_CHECK_FAILED ; 
 int /*<<< orphan*/  SCSI_ASCQ_POWER_LOSS_EXPECTED ; 
 int /*<<< orphan*/  SCSI_ASC_ACCESS_DENIED_INVALID_LUN_ID ; 
 int /*<<< orphan*/  SCSI_ASC_FORMAT_COMMAND_FAILED ; 
 int /*<<< orphan*/  SCSI_ASC_ILLEGAL_BLOCK ; 
 int /*<<< orphan*/  SCSI_ASC_ILLEGAL_COMMAND ; 
 int /*<<< orphan*/  SCSI_ASC_INTERNAL_TARGET_FAILURE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_LOG_BLOCK_APPTAG_CHECK_FAILED ; 
 int /*<<< orphan*/  SCSI_ASC_LOG_BLOCK_GUARD_CHECK_FAILED ; 
 int /*<<< orphan*/  SCSI_ASC_LOG_BLOCK_REFTAG_CHECK_FAILED ; 
 int /*<<< orphan*/  SCSI_ASC_LUN_NOT_READY ; 
 int /*<<< orphan*/  SCSI_ASC_MISCOMPARE_DURING_VERIFY ; 
 int /*<<< orphan*/  SCSI_ASC_NO_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_PERIPHERAL_DEV_WRITE_FAULT ; 
 int /*<<< orphan*/  SCSI_ASC_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_ASC_WARNING ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_trans_status_code(struct sg_io_hdr *hdr, int nvme_sc)
{
	u8 status, sense_key, asc, ascq;
	int res = SNTI_TRANSLATION_SUCCESS;

	/* For non-nvme (Linux) errors, simply return the error code */
	if (nvme_sc < 0)
		return nvme_sc;

	/* Mask DNR, More, and reserved fields */
	nvme_sc &= 0x7FF;

	switch (nvme_sc) {
	/* Generic Command Status */
	case NVME_SC_SUCCESS:
		status = SAM_STAT_GOOD;
		sense_key = NO_SENSE;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_INVALID_OPCODE:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_ILLEGAL_COMMAND;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_INVALID_FIELD:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_INVALID_CDB;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_DATA_XFER_ERROR:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_POWER_LOSS:
		status = SAM_STAT_TASK_ABORTED;
		sense_key = ABORTED_COMMAND;
		asc = SCSI_ASC_WARNING;
		ascq = SCSI_ASCQ_POWER_LOSS_EXPECTED;
		break;
	case NVME_SC_INTERNAL:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = HARDWARE_ERROR;
		asc = SCSI_ASC_INTERNAL_TARGET_FAILURE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_ABORT_REQ:
		status = SAM_STAT_TASK_ABORTED;
		sense_key = ABORTED_COMMAND;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_ABORT_QUEUE:
		status = SAM_STAT_TASK_ABORTED;
		sense_key = ABORTED_COMMAND;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_FUSED_FAIL:
		status = SAM_STAT_TASK_ABORTED;
		sense_key = ABORTED_COMMAND;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_FUSED_MISSING:
		status = SAM_STAT_TASK_ABORTED;
		sense_key = ABORTED_COMMAND;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_INVALID_NS:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_ACCESS_DENIED_INVALID_LUN_ID;
		ascq = SCSI_ASCQ_INVALID_LUN_ID;
		break;
	case NVME_SC_LBA_RANGE:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_ILLEGAL_BLOCK;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_CAP_EXCEEDED:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_NS_NOT_READY:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = NOT_READY;
		asc = SCSI_ASC_LUN_NOT_READY;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;

	/* Command Specific Status */
	case NVME_SC_INVALID_FORMAT:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_FORMAT_COMMAND_FAILED;
		ascq = SCSI_ASCQ_FORMAT_COMMAND_FAILED;
		break;
	case NVME_SC_BAD_ATTRIBUTES:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_INVALID_CDB;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;

	/* Media Errors */
	case NVME_SC_WRITE_FAULT:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_PERIPHERAL_DEV_WRITE_FAULT;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_READ_ERROR:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_UNRECOVERED_READ_ERROR;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_GUARD_CHECK:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_LOG_BLOCK_GUARD_CHECK_FAILED;
		ascq = SCSI_ASCQ_LOG_BLOCK_GUARD_CHECK_FAILED;
		break;
	case NVME_SC_APPTAG_CHECK:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_LOG_BLOCK_APPTAG_CHECK_FAILED;
		ascq = SCSI_ASCQ_LOG_BLOCK_APPTAG_CHECK_FAILED;
		break;
	case NVME_SC_REFTAG_CHECK:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MEDIUM_ERROR;
		asc = SCSI_ASC_LOG_BLOCK_REFTAG_CHECK_FAILED;
		ascq = SCSI_ASCQ_LOG_BLOCK_REFTAG_CHECK_FAILED;
		break;
	case NVME_SC_COMPARE_FAILED:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = MISCOMPARE;
		asc = SCSI_ASC_MISCOMPARE_DURING_VERIFY;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	case NVME_SC_ACCESS_DENIED:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_ACCESS_DENIED_INVALID_LUN_ID;
		ascq = SCSI_ASCQ_INVALID_LUN_ID;
		break;

	/* Unspecified/Default */
	case NVME_SC_CMDID_CONFLICT:
	case NVME_SC_CMD_SEQ_ERROR:
	case NVME_SC_CQ_INVALID:
	case NVME_SC_QID_INVALID:
	case NVME_SC_QUEUE_SIZE:
	case NVME_SC_ABORT_LIMIT:
	case NVME_SC_ABORT_MISSING:
	case NVME_SC_ASYNC_LIMIT:
	case NVME_SC_FIRMWARE_SLOT:
	case NVME_SC_FIRMWARE_IMAGE:
	case NVME_SC_INVALID_VECTOR:
	case NVME_SC_INVALID_LOG_PAGE:
	default:
		status = SAM_STAT_CHECK_CONDITION;
		sense_key = ILLEGAL_REQUEST;
		asc = SCSI_ASC_NO_SENSE;
		ascq = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		break;
	}

	res = nvme_trans_completion(hdr, status, sense_key, asc, ascq);

	return res;
}