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

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 unsigned int SCSI_PROT_NORMAL ; 
 unsigned int SCSI_PROT_READ_INSERT ; 
 unsigned int SCSI_PROT_READ_PASS ; 
 unsigned int SCSI_PROT_READ_STRIP ; 
 unsigned int SCSI_PROT_WRITE_INSERT ; 
 unsigned int SCSI_PROT_WRITE_PASS ; 
 unsigned int SCSI_PROT_WRITE_STRIP ; 
 unsigned int scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_prot_op (struct scsi_cmnd*,unsigned int) ; 
 int /*<<< orphan*/  scsi_set_prot_type (struct scsi_cmnd*,unsigned int) ; 

__attribute__((used)) static void sd_prot_op(struct scsi_cmnd *scmd, unsigned int dif)
{
	unsigned int prot_op = SCSI_PROT_NORMAL;
	unsigned int dix = scsi_prot_sg_count(scmd);

	if (scmd->sc_data_direction == DMA_FROM_DEVICE) {
		if (dif && dix)
			prot_op = SCSI_PROT_READ_PASS;
		else if (dif && !dix)
			prot_op = SCSI_PROT_READ_STRIP;
		else if (!dif && dix)
			prot_op = SCSI_PROT_READ_INSERT;
	} else {
		if (dif && dix)
			prot_op = SCSI_PROT_WRITE_PASS;
		else if (dif && !dix)
			prot_op = SCSI_PROT_WRITE_INSERT;
		else if (!dif && dix)
			prot_op = SCSI_PROT_WRITE_STRIP;
	}

	scsi_set_prot_op(scmd, prot_op);
	scsi_set_prot_type(scmd, dif);
}