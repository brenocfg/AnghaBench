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
typedef  unsigned int u8 ;
struct sg_io_hdr {int /*<<< orphan*/  cmd_len; int /*<<< orphan*/ * cmdp; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int BLK_MAX_CDB ; 
 int EFAULT ; 
 int EMSGSIZE ; 
#define  FORMAT_UNIT 153 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
#define  INQUIRY 152 
 int /*<<< orphan*/  IS_READ_CAP_16 (unsigned int*) ; 
#define  LOG_SENSE 151 
#define  MODE_SELECT 150 
#define  MODE_SELECT_10 149 
#define  MODE_SENSE 148 
#define  MODE_SENSE_10 147 
#define  READ_10 146 
#define  READ_12 145 
#define  READ_16 144 
#define  READ_6 143 
#define  READ_CAPACITY 142 
#define  REPORT_LUNS 141 
#define  REQUEST_SENSE 140 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_ILLEGAL_COMMAND ; 
#define  SECURITY_PROTOCOL_IN 139 
#define  SECURITY_PROTOCOL_OUT 138 
#define  SERVICE_ACTION_IN 137 
#define  START_STOP 136 
#define  SYNCHRONIZE_CACHE 135 
#define  TEST_UNIT_READY 134 
#define  UNMAP 133 
#define  WRITE_10 132 
#define  WRITE_12 131 
#define  WRITE_16 130 
#define  WRITE_6 129 
#define  WRITE_BUFFER 128 
 scalar_t__ copy_from_user (unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_format_unit (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_inquiry (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_io (struct nvme_ns*,struct sg_io_hdr*,int,unsigned int*) ; 
 int nvme_trans_log_sense (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_mode_select (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_mode_sense (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_read_capacity (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_report_luns (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_request_sense (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_security_protocol (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_start_stop (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_synchronize_cache (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_test_unit_ready (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_unmap (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 
 int nvme_trans_write_buffer (struct nvme_ns*,struct sg_io_hdr*,unsigned int*) ; 

__attribute__((used)) static int nvme_scsi_translate(struct nvme_ns *ns, struct sg_io_hdr *hdr)
{
	u8 cmd[BLK_MAX_CDB];
	int retcode;
	unsigned int opcode;

	if (hdr->cmdp == NULL)
		return -EMSGSIZE;
	if (copy_from_user(cmd, hdr->cmdp, hdr->cmd_len))
		return -EFAULT;

	opcode = cmd[0];

	switch (opcode) {
	case READ_6:
	case READ_10:
	case READ_12:
	case READ_16:
		retcode = nvme_trans_io(ns, hdr, 0, cmd);
		break;
	case WRITE_6:
	case WRITE_10:
	case WRITE_12:
	case WRITE_16:
		retcode = nvme_trans_io(ns, hdr, 1, cmd);
		break;
	case INQUIRY:
		retcode = nvme_trans_inquiry(ns, hdr, cmd);
		break;
	case LOG_SENSE:
		retcode = nvme_trans_log_sense(ns, hdr, cmd);
		break;
	case MODE_SELECT:
	case MODE_SELECT_10:
		retcode = nvme_trans_mode_select(ns, hdr, cmd);
		break;
	case MODE_SENSE:
	case MODE_SENSE_10:
		retcode = nvme_trans_mode_sense(ns, hdr, cmd);
		break;
	case READ_CAPACITY:
		retcode = nvme_trans_read_capacity(ns, hdr, cmd);
		break;
	case SERVICE_ACTION_IN:
		if (IS_READ_CAP_16(cmd))
			retcode = nvme_trans_read_capacity(ns, hdr, cmd);
		else
			goto out;
		break;
	case REPORT_LUNS:
		retcode = nvme_trans_report_luns(ns, hdr, cmd);
		break;
	case REQUEST_SENSE:
		retcode = nvme_trans_request_sense(ns, hdr, cmd);
		break;
	case SECURITY_PROTOCOL_IN:
	case SECURITY_PROTOCOL_OUT:
		retcode = nvme_trans_security_protocol(ns, hdr, cmd);
		break;
	case START_STOP:
		retcode = nvme_trans_start_stop(ns, hdr, cmd);
		break;
	case SYNCHRONIZE_CACHE:
		retcode = nvme_trans_synchronize_cache(ns, hdr, cmd);
		break;
	case FORMAT_UNIT:
		retcode = nvme_trans_format_unit(ns, hdr, cmd);
		break;
	case TEST_UNIT_READY:
		retcode = nvme_trans_test_unit_ready(ns, hdr, cmd);
		break;
	case WRITE_BUFFER:
		retcode = nvme_trans_write_buffer(ns, hdr, cmd);
		break;
	case UNMAP:
		retcode = nvme_trans_unmap(ns, hdr, cmd);
		break;
	default:
 out:
		retcode = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
				ILLEGAL_REQUEST, SCSI_ASC_ILLEGAL_COMMAND,
				SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		break;
	}
	return retcode;
}