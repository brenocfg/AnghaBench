#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct sli3_bg_fields {scalar_t__ bgstat; scalar_t__ bghm; } ;
struct scsi_dif_tuple {int dummy; } ;
struct scsi_cmnd {int* cmnd; int result; int* sense_buffer; int /*<<< orphan*/  request; TYPE_3__* device; } ;
struct lpfc_scsi_buf {struct scsi_cmnd* pCmd; } ;
struct TYPE_4__ {struct sli3_bg_fields sli3_bg; } ;
struct TYPE_5__ {TYPE_1__ unsli3; } ;
struct lpfc_iocbq {TYPE_2__ iocb; } ;
struct lpfc_hba {int /*<<< orphan*/  bg_apptag_err_cnt; int /*<<< orphan*/  bg_reftag_err_cnt; int /*<<< orphan*/  bg_guard_err_cnt; } ;
struct TYPE_6__ {scalar_t__ sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ABORT ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int DRIVER_SENSE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int LOG_BG ; 
 int LOG_FCP ; 
 scalar_t__ LPFC_PG_TYPE_DIF_BUF ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
#define  SCSI_PROT_READ_INSERT 133 
#define  SCSI_PROT_READ_PASS 132 
#define  SCSI_PROT_READ_STRIP 131 
#define  SCSI_PROT_WRITE_INSERT 130 
#define  SCSI_PROT_WRITE_PASS 129 
#define  SCSI_PROT_WRITE_STRIP 128 
 int ScsiResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _dump_buf_done ; 
 int /*<<< orphan*/  _dump_buf_lock ; 
 int /*<<< orphan*/  blk_rq_sectors (int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_bgs_get_apptag_err (scalar_t__) ; 
 scalar_t__ lpfc_bgs_get_guard_err (scalar_t__) ; 
 scalar_t__ lpfc_bgs_get_hi_water_mark_present (scalar_t__) ; 
 scalar_t__ lpfc_bgs_get_invalid_prof (scalar_t__) ; 
 scalar_t__ lpfc_bgs_get_reftag_err (scalar_t__) ; 
 scalar_t__ lpfc_bgs_get_uninit_dif_block (scalar_t__) ; 
 int /*<<< orphan*/  lpfc_calc_bg_err (struct lpfc_hba*,struct lpfc_scsi_buf*) ; 
 int /*<<< orphan*/  lpfc_debug_save_data (struct lpfc_hba*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  lpfc_debug_save_dif (struct lpfc_hba*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*,int,...) ; 
 scalar_t__ lpfc_prot_group_type (struct lpfc_hba*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (scalar_t__,int*) ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int,int*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ scsi_get_lba (struct scsi_cmnd*) ; 
 int scsi_get_prot_op (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lpfc_parse_bg_err(struct lpfc_hba *phba, struct lpfc_scsi_buf *lpfc_cmd,
			struct lpfc_iocbq *pIocbOut)
{
	struct scsi_cmnd *cmd = lpfc_cmd->pCmd;
	struct sli3_bg_fields *bgf = &pIocbOut->iocb.unsli3.sli3_bg;
	int ret = 0;
	uint32_t bghm = bgf->bghm;
	uint32_t bgstat = bgf->bgstat;
	uint64_t failing_sector = 0;

	spin_lock(&_dump_buf_lock);
	if (!_dump_buf_done) {
		lpfc_printf_log(phba, KERN_ERR, LOG_BG,  "9070 BLKGRD: Saving"
			" Data for %u blocks to debugfs\n",
				(cmd->cmnd[7] << 8 | cmd->cmnd[8]));
		lpfc_debug_save_data(phba, cmd);

		/* If we have a prot sgl, save the DIF buffer */
		if (lpfc_prot_group_type(phba, cmd) ==
				LPFC_PG_TYPE_DIF_BUF) {
			lpfc_printf_log(phba, KERN_ERR, LOG_BG, "9071 BLKGRD: "
				"Saving DIF for %u blocks to debugfs\n",
				(cmd->cmnd[7] << 8 | cmd->cmnd[8]));
			lpfc_debug_save_dif(phba, cmd);
		}

		_dump_buf_done = 1;
	}
	spin_unlock(&_dump_buf_lock);

	if (lpfc_bgs_get_invalid_prof(bgstat)) {
		cmd->result = ScsiResult(DID_ERROR, 0);
		lpfc_printf_log(phba, KERN_WARNING, LOG_FCP | LOG_BG,
				"9072 BLKGRD: Invalid BG Profile in cmd"
				" 0x%x lba 0x%llx blk cnt 0x%x "
				"bgstat=x%x bghm=x%x\n", cmd->cmnd[0],
				(unsigned long long)scsi_get_lba(cmd),
				blk_rq_sectors(cmd->request), bgstat, bghm);
		ret = (-1);
		goto out;
	}

	if (lpfc_bgs_get_uninit_dif_block(bgstat)) {
		cmd->result = ScsiResult(DID_ERROR, 0);
		lpfc_printf_log(phba, KERN_WARNING, LOG_FCP | LOG_BG,
				"9073 BLKGRD: Invalid BG PDIF Block in cmd"
				" 0x%x lba 0x%llx blk cnt 0x%x "
				"bgstat=x%x bghm=x%x\n", cmd->cmnd[0],
				(unsigned long long)scsi_get_lba(cmd),
				blk_rq_sectors(cmd->request), bgstat, bghm);
		ret = (-1);
		goto out;
	}

	if (lpfc_bgs_get_guard_err(bgstat)) {
		ret = 1;

		scsi_build_sense_buffer(1, cmd->sense_buffer, ILLEGAL_REQUEST,
				0x10, 0x1);
		cmd->result = DRIVER_SENSE << 24
			| ScsiResult(DID_ABORT, SAM_STAT_CHECK_CONDITION);
		phba->bg_guard_err_cnt++;
		lpfc_printf_log(phba, KERN_WARNING, LOG_FCP | LOG_BG,
				"9055 BLKGRD: Guard Tag error in cmd"
				" 0x%x lba 0x%llx blk cnt 0x%x "
				"bgstat=x%x bghm=x%x\n", cmd->cmnd[0],
				(unsigned long long)scsi_get_lba(cmd),
				blk_rq_sectors(cmd->request), bgstat, bghm);
	}

	if (lpfc_bgs_get_reftag_err(bgstat)) {
		ret = 1;

		scsi_build_sense_buffer(1, cmd->sense_buffer, ILLEGAL_REQUEST,
				0x10, 0x3);
		cmd->result = DRIVER_SENSE << 24
			| ScsiResult(DID_ABORT, SAM_STAT_CHECK_CONDITION);

		phba->bg_reftag_err_cnt++;
		lpfc_printf_log(phba, KERN_WARNING, LOG_FCP | LOG_BG,
				"9056 BLKGRD: Ref Tag error in cmd"
				" 0x%x lba 0x%llx blk cnt 0x%x "
				"bgstat=x%x bghm=x%x\n", cmd->cmnd[0],
				(unsigned long long)scsi_get_lba(cmd),
				blk_rq_sectors(cmd->request), bgstat, bghm);
	}

	if (lpfc_bgs_get_apptag_err(bgstat)) {
		ret = 1;

		scsi_build_sense_buffer(1, cmd->sense_buffer, ILLEGAL_REQUEST,
				0x10, 0x2);
		cmd->result = DRIVER_SENSE << 24
			| ScsiResult(DID_ABORT, SAM_STAT_CHECK_CONDITION);

		phba->bg_apptag_err_cnt++;
		lpfc_printf_log(phba, KERN_WARNING, LOG_FCP | LOG_BG,
				"9061 BLKGRD: App Tag error in cmd"
				" 0x%x lba 0x%llx blk cnt 0x%x "
				"bgstat=x%x bghm=x%x\n", cmd->cmnd[0],
				(unsigned long long)scsi_get_lba(cmd),
				blk_rq_sectors(cmd->request), bgstat, bghm);
	}

	if (lpfc_bgs_get_hi_water_mark_present(bgstat)) {
		/*
		 * setup sense data descriptor 0 per SPC-4 as an information
		 * field, and put the failing LBA in it.
		 * This code assumes there was also a guard/app/ref tag error
		 * indication.
		 */
		cmd->sense_buffer[7] = 0xc;   /* Additional sense length */
		cmd->sense_buffer[8] = 0;     /* Information descriptor type */
		cmd->sense_buffer[9] = 0xa;   /* Additional descriptor length */
		cmd->sense_buffer[10] = 0x80; /* Validity bit */

		/* bghm is a "on the wire" FC frame based count */
		switch (scsi_get_prot_op(cmd)) {
		case SCSI_PROT_READ_INSERT:
		case SCSI_PROT_WRITE_STRIP:
			bghm /= cmd->device->sector_size;
			break;
		case SCSI_PROT_READ_STRIP:
		case SCSI_PROT_WRITE_INSERT:
		case SCSI_PROT_READ_PASS:
		case SCSI_PROT_WRITE_PASS:
			bghm /= (cmd->device->sector_size +
				sizeof(struct scsi_dif_tuple));
			break;
		}

		failing_sector = scsi_get_lba(cmd);
		failing_sector += bghm;

		/* Descriptor Information */
		put_unaligned_be64(failing_sector, &cmd->sense_buffer[12]);
	}

	if (!ret) {
		/* No error was reported - problem in FW? */
		lpfc_printf_log(phba, KERN_WARNING, LOG_FCP | LOG_BG,
				"9057 BLKGRD: Unknown error in cmd"
				" 0x%x lba 0x%llx blk cnt 0x%x "
				"bgstat=x%x bghm=x%x\n", cmd->cmnd[0],
				(unsigned long long)scsi_get_lba(cmd),
				blk_rq_sectors(cmd->request), bgstat, bghm);

		/* Calcuate what type of error it was */
		lpfc_calc_bg_err(phba, lpfc_cmd);
	}
out:
	return ret;
}