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
struct scsi_cmnd {int result; } ;
struct ata_queued_cmd {void (* scsidone ) (struct scsi_cmnd*) ;int /*<<< orphan*/  n_elem; int /*<<< orphan*/  sg; struct scsi_cmnd* scsicmd; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int DID_OK ; 
 int QUEUE_FULL ; 
 struct ata_queued_cmd* ata_qc_new_init (struct ata_device*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

__attribute__((used)) static struct ata_queued_cmd *ata_scsi_qc_new(struct ata_device *dev,
					      struct scsi_cmnd *cmd,
					      void (*done)(struct scsi_cmnd *))
{
	struct ata_queued_cmd *qc;

	qc = ata_qc_new_init(dev);
	if (qc) {
		qc->scsicmd = cmd;
		qc->scsidone = done;

		qc->sg = scsi_sglist(cmd);
		qc->n_elem = scsi_sg_count(cmd);
	} else {
		cmd->result = (DID_OK << 16) | (QUEUE_FULL << 1);
		done(cmd);
	}

	return qc;
}