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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
#define  ACTIVATE_DEFERRED_MICROCODE 130 
 int BYTES_TO_DWORDS ; 
#define  DOWNLOAD_SAVE_ACTIVATE 129 
#define  DOWNLOAD_SAVE_DEFER_ACTIVATE 128 
 int GET_U24_FROM_CDB (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_U8_FROM_CDB (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 scalar_t__ NVME_MAX_FIRMWARE_SLOT ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  WRITE_BUFFER_CDB_BUFFER_ID_OFFSET ; 
 int /*<<< orphan*/  WRITE_BUFFER_CDB_BUFFER_OFFSET_OFFSET ; 
 scalar_t__ WRITE_BUFFER_CDB_MODE_MASK ; 
 int /*<<< orphan*/  WRITE_BUFFER_CDB_MODE_OFFSET ; 
 int /*<<< orphan*/  WRITE_BUFFER_CDB_PARM_LIST_LENGTH_OFFSET ; 
 int /*<<< orphan*/  nvme_admin_activate_fw ; 
 int /*<<< orphan*/  nvme_admin_download_fw ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_send_fw_cmd (struct nvme_ns*,struct sg_io_hdr*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 

__attribute__((used)) static int nvme_trans_write_buffer(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u32 buffer_offset, parm_list_length;
	u8 buffer_id, mode;

	parm_list_length =
		GET_U24_FROM_CDB(cmd, WRITE_BUFFER_CDB_PARM_LIST_LENGTH_OFFSET);
	if (parm_list_length % BYTES_TO_DWORDS != 0) {
		/* NVMe expects Firmware file to be a whole number of DWORDS */
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}
	buffer_id = GET_U8_FROM_CDB(cmd, WRITE_BUFFER_CDB_BUFFER_ID_OFFSET);
	if (buffer_id > NVME_MAX_FIRMWARE_SLOT) {
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}
	mode = GET_U8_FROM_CDB(cmd, WRITE_BUFFER_CDB_MODE_OFFSET) &
						WRITE_BUFFER_CDB_MODE_MASK;
	buffer_offset =
		GET_U24_FROM_CDB(cmd, WRITE_BUFFER_CDB_BUFFER_OFFSET_OFFSET);

	switch (mode) {
	case DOWNLOAD_SAVE_ACTIVATE:
		res = nvme_trans_send_fw_cmd(ns, hdr, nvme_admin_download_fw,
						parm_list_length, buffer_offset,
						buffer_id);
		if (res != SNTI_TRANSLATION_SUCCESS)
			goto out;
		res = nvme_trans_send_fw_cmd(ns, hdr, nvme_admin_activate_fw,
						parm_list_length, buffer_offset,
						buffer_id);
		break;
	case DOWNLOAD_SAVE_DEFER_ACTIVATE:
		res = nvme_trans_send_fw_cmd(ns, hdr, nvme_admin_download_fw,
						parm_list_length, buffer_offset,
						buffer_id);
		break;
	case ACTIVATE_DEFERRED_MICROCODE:
		res = nvme_trans_send_fw_cmd(ns, hdr, nvme_admin_activate_fw,
						parm_list_length, buffer_offset,
						buffer_id);
		break;
	default:
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		break;
	}

 out:
	return res;
}