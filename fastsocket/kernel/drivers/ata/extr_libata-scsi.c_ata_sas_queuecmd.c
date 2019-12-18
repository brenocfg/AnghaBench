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
struct scsi_cmnd {int result; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ata_port {TYPE_1__ link; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int __ata_scsi_queuecmd (struct scsi_cmnd*,void (*) (struct scsi_cmnd*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_dev_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_dump_cdb (struct ata_port*,struct scsi_cmnd*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

int ata_sas_queuecmd(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *),
		     struct ata_port *ap)
{
	int rc = 0;

	ata_scsi_dump_cdb(ap, cmd);

	if (likely(ata_dev_enabled(ap->link.device)))
		rc = __ata_scsi_queuecmd(cmd, done, ap->link.device);
	else {
		cmd->result = (DID_BAD_TARGET << 16);
		done(cmd);
	}
	return rc;
}