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
struct scsi_device {struct Scsi_Host* host; } ;
struct scsi_cmnd {int result; struct scsi_device* device; } ;
struct ata_port {int /*<<< orphan*/  lock; } ;
struct ata_device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int __ata_scsi_queuecmd (struct scsi_cmnd*,void (*) (struct scsi_cmnd*),struct ata_device*) ; 
 int /*<<< orphan*/  ata_scsi_dump_cdb (struct ata_port*,struct scsi_cmnd*) ; 
 struct ata_device* ata_scsi_find_dev (struct ata_port*,struct scsi_device*) ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 scalar_t__ likely (struct ata_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

int ata_scsi_queuecmd(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *))
{
	struct ata_port *ap;
	struct ata_device *dev;
	struct scsi_device *scsidev = cmd->device;
	struct Scsi_Host *shost = scsidev->host;
	int rc = 0;

	ap = ata_shost_to_port(shost);

	spin_unlock(shost->host_lock);
	spin_lock(ap->lock);

	ata_scsi_dump_cdb(ap, cmd);

	dev = ata_scsi_find_dev(ap, scsidev);
	if (likely(dev))
		rc = __ata_scsi_queuecmd(cmd, done, dev);
	else {
		cmd->result = (DID_BAD_TARGET << 16);
		done(cmd);
	}

	spin_unlock(ap->lock);
	spin_lock(shost->host_lock);
	return rc;
}