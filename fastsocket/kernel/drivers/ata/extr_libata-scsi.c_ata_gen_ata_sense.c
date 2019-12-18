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
typedef  int u64 ;
struct scsi_cmnd {unsigned char* sense_buffer; int result; } ;
struct ata_taskfile {int command; int /*<<< orphan*/  feature; } ;
struct ata_queued_cmd {struct ata_taskfile result_tf; TYPE_2__* ap; scalar_t__ err_mask; struct scsi_cmnd* scsicmd; struct ata_device* dev; } ;
struct ata_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  print_id; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/ * error_handler; } ;

/* Variables and functions */
 int ATA_BUSY ; 
 int ATA_DF ; 
 int ATA_DRQ ; 
 int ATA_ERR ; 
 int DRIVER_SENSE ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int ata_tf_read_block (struct ata_taskfile*,struct ata_device*) ; 
 int /*<<< orphan*/  ata_to_sense_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ata_gen_ata_sense(struct ata_queued_cmd *qc)
{
	struct ata_device *dev = qc->dev;
	struct scsi_cmnd *cmd = qc->scsicmd;
	struct ata_taskfile *tf = &qc->result_tf;
	unsigned char *sb = cmd->sense_buffer;
	unsigned char *desc = sb + 8;
	int verbose = qc->ap->ops->error_handler == NULL;
	u64 block;

	memset(sb, 0, SCSI_SENSE_BUFFERSIZE);

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	/* sense data is current and format is descriptor */
	sb[0] = 0x72;

	/* Use ata_to_sense_error() to map status register bits
	 * onto sense key, asc & ascq.
	 */
	if (qc->err_mask ||
	    tf->command & (ATA_BUSY | ATA_DF | ATA_ERR | ATA_DRQ)) {
		ata_to_sense_error(qc->ap->print_id, tf->command, tf->feature,
				   &sb[1], &sb[2], &sb[3], verbose);
		sb[1] &= 0x0f;
	}

	block = ata_tf_read_block(&qc->result_tf, dev);

	/* information sense data descriptor */
	sb[7] = 12;
	desc[0] = 0x00;
	desc[1] = 10;

	desc[2] |= 0x80;	/* valid */
	desc[6] = block >> 40;
	desc[7] = block >> 32;
	desc[8] = block >> 24;
	desc[9] = block >> 16;
	desc[10] = block >> 8;
	desc[11] = block;
}