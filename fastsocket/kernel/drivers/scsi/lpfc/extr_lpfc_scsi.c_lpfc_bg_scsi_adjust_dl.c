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
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct lpfc_scsi_buf {struct scsi_cmnd* pCmd; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ SCSI_PROT_READ_INSERT ; 
 scalar_t__ SCSI_PROT_WRITE_STRIP ; 
 int lpfc_cmd_blksize (struct scsi_cmnd*) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 scalar_t__ scsi_get_prot_op (struct scsi_cmnd*) ; 

__attribute__((used)) static int
lpfc_bg_scsi_adjust_dl(struct lpfc_hba *phba,
		       struct lpfc_scsi_buf *lpfc_cmd)
{
	struct scsi_cmnd *sc = lpfc_cmd->pCmd;
	int fcpdl;

	fcpdl = scsi_bufflen(sc);

	/* Check if there is protection data on the wire */
	if (sc->sc_data_direction == DMA_FROM_DEVICE) {
		/* Read check for protection data */
		if (scsi_get_prot_op(sc) ==  SCSI_PROT_READ_INSERT)
			return fcpdl;

	} else {
		/* Write check for protection data */
		if (scsi_get_prot_op(sc) ==  SCSI_PROT_WRITE_STRIP)
			return fcpdl;
	}

	/*
	 * If we are in DIF Type 1 mode every data block has a 8 byte
	 * DIF (trailer) attached to it. Must ajust FCP data length
	 * to account for the protection data.
	 */
	fcpdl += (fcpdl / lpfc_cmd_blksize(sc)) * 8;

	return fcpdl;
}