#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct scsi_cmnd {int* cmnd; int cmd_len; int /*<<< orphan*/  result; } ;
struct ata_taskfile {int flags; int nsect; int lbah; int lbam; int lbal; int /*<<< orphan*/  command; int /*<<< orphan*/  device; int /*<<< orphan*/  protocol; } ;
struct ata_queued_cmd {TYPE_2__* ap; TYPE_1__* dev; struct ata_taskfile tf; struct scsi_cmnd* scsicmd; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_STANDBYNOW1 ; 
 int /*<<< orphan*/  ATA_CMD_VERIFY ; 
 int ATA_DFLAG_LBA ; 
 int ATA_FLAG_NO_HIBERNATE_SPINDOWN ; 
 int ATA_FLAG_NO_POWEROFF_SPINDOWN ; 
 int /*<<< orphan*/  ATA_LBA ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ system_entering_hibernation () ; 
 scalar_t__ system_state ; 

__attribute__((used)) static unsigned int ata_scsi_start_stop_xlat(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct ata_taskfile *tf = &qc->tf;
	const u8 *cdb = scmd->cmnd;

	if (scmd->cmd_len < 5)
		goto invalid_fld;

	tf->flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;
	tf->protocol = ATA_PROT_NODATA;
	if (cdb[1] & 0x1) {
		;	/* ignore IMMED bit, violates sat-r05 */
	}
	if (cdb[4] & 0x2)
		goto invalid_fld;       /* LOEJ bit set not supported */
	if (((cdb[4] >> 4) & 0xf) != 0)
		goto invalid_fld;       /* power conditions not supported */

	if (cdb[4] & 0x1) {
		tf->nsect = 1;	/* 1 sector, lba=0 */

		if (qc->dev->flags & ATA_DFLAG_LBA) {
			tf->flags |= ATA_TFLAG_LBA;

			tf->lbah = 0x0;
			tf->lbam = 0x0;
			tf->lbal = 0x0;
			tf->device |= ATA_LBA;
		} else {
			/* CHS */
			tf->lbal = 0x1; /* sect */
			tf->lbam = 0x0; /* cyl low */
			tf->lbah = 0x0; /* cyl high */
		}

		tf->command = ATA_CMD_VERIFY;	/* READ VERIFY */
	} else {
		/* Some odd clown BIOSen issue spindown on power off (ACPI S4
		 * or S5) causing some drives to spin up and down again.
		 */
		if ((qc->ap->flags & ATA_FLAG_NO_POWEROFF_SPINDOWN) &&
		    system_state == SYSTEM_POWER_OFF)
			goto skip;

		if ((qc->ap->flags & ATA_FLAG_NO_HIBERNATE_SPINDOWN) &&
		     system_entering_hibernation())
			goto skip;

		/* Issue ATA STANDBY IMMEDIATE command */
		tf->command = ATA_CMD_STANDBYNOW1;
	}

	/*
	 * Standby and Idle condition timers could be implemented but that
	 * would require libata to implement the Power condition mode page
	 * and allow the user to change it. Changing mode pages requires
	 * MODE SELECT to be implemented.
	 */

	return 0;

 invalid_fld:
	ata_scsi_set_sense(scmd, ILLEGAL_REQUEST, 0x24, 0x0);
	/* "Invalid field in cbd" */
	return 1;
 skip:
	scmd->result = SAM_STAT_GOOD;
	return 1;
}