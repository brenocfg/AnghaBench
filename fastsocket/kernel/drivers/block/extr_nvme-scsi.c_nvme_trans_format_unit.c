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
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 scalar_t__ FORMAT_UNIT_CDB_FORMAT_DATA_MASK ; 
 int /*<<< orphan*/  FORMAT_UNIT_CDB_FORMAT_DATA_OFFSET ; 
 scalar_t__ FORMAT_UNIT_CDB_FORMAT_PROT_INFO_MASK ; 
 int /*<<< orphan*/  FORMAT_UNIT_CDB_FORMAT_PROT_INFO_OFFSET ; 
 scalar_t__ FORMAT_UNIT_CDB_FORMAT_PROT_INFO_SHIFT ; 
 scalar_t__ FORMAT_UNIT_CDB_LONG_LIST_MASK ; 
 int /*<<< orphan*/  FORMAT_UNIT_CDB_LONG_LIST_OFFSET ; 
 scalar_t__ FORMAT_UNIT_LONG_PARM_LIST_LEN ; 
 scalar_t__ FORMAT_UNIT_SHORT_PARM_LIST_LEN ; 
 scalar_t__ GET_U8_FROM_CDB (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  nvme_admin_activate_fw ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_fmt_get_parm_header (struct sg_io_hdr*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int nvme_trans_fmt_send_cmd (struct nvme_ns*,struct sg_io_hdr*,scalar_t__) ; 
 int nvme_trans_fmt_set_blk_size_count (struct nvme_ns*,struct sg_io_hdr*) ; 
 int nvme_trans_send_fw_cmd (struct nvme_ns*,struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_trans_format_unit(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u8 parm_hdr_len = 0;
	u8 nvme_pf_code = 0;
	u8 format_prot_info, long_list, format_data;

	format_prot_info = GET_U8_FROM_CDB(cmd,
				FORMAT_UNIT_CDB_FORMAT_PROT_INFO_OFFSET);
	long_list = GET_U8_FROM_CDB(cmd, FORMAT_UNIT_CDB_LONG_LIST_OFFSET);
	format_data = GET_U8_FROM_CDB(cmd, FORMAT_UNIT_CDB_FORMAT_DATA_OFFSET);

	format_prot_info = (format_prot_info &
				FORMAT_UNIT_CDB_FORMAT_PROT_INFO_MASK) >>
				FORMAT_UNIT_CDB_FORMAT_PROT_INFO_SHIFT;
	long_list &= FORMAT_UNIT_CDB_LONG_LIST_MASK;
	format_data &= FORMAT_UNIT_CDB_FORMAT_DATA_MASK;

	if (format_data != 0) {
		if (format_prot_info != 0) {
			if (long_list == 0)
				parm_hdr_len = FORMAT_UNIT_SHORT_PARM_LIST_LEN;
			else
				parm_hdr_len = FORMAT_UNIT_LONG_PARM_LIST_LEN;
		}
	} else if (format_data == 0 && format_prot_info != 0) {
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}

	/* Get parm header from data-in/out buffer */
	/*
	 * According to the translation spec, the only fields in the parameter
	 * list we are concerned with are in the header. So allocate only that.
	 */
	if (parm_hdr_len > 0) {
		res = nvme_trans_fmt_get_parm_header(hdr, parm_hdr_len,
					format_prot_info, &nvme_pf_code);
		if (res != SNTI_TRANSLATION_SUCCESS)
			goto out;
	}

	/* Attempt to activate any previously downloaded firmware image */
	res = nvme_trans_send_fw_cmd(ns, hdr, nvme_admin_activate_fw, 0, 0, 0);

	/* Determine Block size and count and send format command */
	res = nvme_trans_fmt_set_blk_size_count(ns, hdr);
	if (res != SNTI_TRANSLATION_SUCCESS)
		goto out;

	res = nvme_trans_fmt_send_cmd(ns, hdr, nvme_pf_code);

 out:
	return res;
}