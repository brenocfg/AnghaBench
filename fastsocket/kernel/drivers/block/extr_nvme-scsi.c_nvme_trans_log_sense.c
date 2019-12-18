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
typedef  int /*<<< orphan*/  u16 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_U16_FROM_CDB (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_U8_FROM_CDB (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
#define  LOG_PAGE_INFORMATIONAL_EXCEPTIONS_PAGE 130 
#define  LOG_PAGE_SUPPORTED_LOG_PAGES_PAGE 129 
#define  LOG_PAGE_TEMPERATURE_PAGE 128 
 int /*<<< orphan*/  LOG_SENSE_CDB_ALLOC_LENGTH_OFFSET ; 
 scalar_t__ LOG_SENSE_CDB_PAGE_CODE_MASK ; 
 scalar_t__ LOG_SENSE_CDB_PC_CUMULATIVE_VALUES ; 
 scalar_t__ LOG_SENSE_CDB_PC_MASK ; 
 int /*<<< orphan*/  LOG_SENSE_CDB_PC_OFFSET ; 
 scalar_t__ LOG_SENSE_CDB_PC_SHIFT ; 
 scalar_t__ LOG_SENSE_CDB_SP_NOT_ENABLED ; 
 int /*<<< orphan*/  LOG_SENSE_CDB_SP_OFFSET ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_log_info_exceptions (struct nvme_ns*,struct sg_io_hdr*,int /*<<< orphan*/ ) ; 
 int nvme_trans_log_supp_pages (struct nvme_ns*,struct sg_io_hdr*,int /*<<< orphan*/ ) ; 
 int nvme_trans_log_temperature (struct nvme_ns*,struct sg_io_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_trans_log_sense(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u16 alloc_len;
	u8 sp;
	u8 pc;
	u8 page_code;

	sp = GET_U8_FROM_CDB(cmd, LOG_SENSE_CDB_SP_OFFSET);
	if (sp != LOG_SENSE_CDB_SP_NOT_ENABLED) {
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}
	pc = GET_U8_FROM_CDB(cmd, LOG_SENSE_CDB_PC_OFFSET);
	page_code = pc & LOG_SENSE_CDB_PAGE_CODE_MASK;
	pc = (pc & LOG_SENSE_CDB_PC_MASK) >> LOG_SENSE_CDB_PC_SHIFT;
	if (pc != LOG_SENSE_CDB_PC_CUMULATIVE_VALUES) {
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}
	alloc_len = GET_U16_FROM_CDB(cmd, LOG_SENSE_CDB_ALLOC_LENGTH_OFFSET);
	switch (page_code) {
	case LOG_PAGE_SUPPORTED_LOG_PAGES_PAGE:
		res = nvme_trans_log_supp_pages(ns, hdr, alloc_len);
		break;
	case LOG_PAGE_INFORMATIONAL_EXCEPTIONS_PAGE:
		res = nvme_trans_log_info_exceptions(ns, hdr, alloc_len);
		break;
	case LOG_PAGE_TEMPERATURE_PAGE:
		res = nvme_trans_log_temperature(ns, hdr, alloc_len);
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