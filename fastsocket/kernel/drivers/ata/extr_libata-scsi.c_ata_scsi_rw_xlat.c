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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct scsi_cmnd {int* cmnd; int cmd_len; int /*<<< orphan*/  result; TYPE_1__* device; } ;
struct ata_queued_cmd {int nbytes; int /*<<< orphan*/  tag; int /*<<< orphan*/  dev; int /*<<< orphan*/  tf; int /*<<< orphan*/  flags; struct scsi_cmnd* scsicmd; } ;
struct TYPE_2__ {int sector_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_QCFLAG_IO ; 
 unsigned int ATA_TFLAG_FUA ; 
 unsigned int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ERANGE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
#define  READ_10 133 
#define  READ_16 132 
#define  READ_6 131 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
#define  WRITE_10 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int ata_build_rw_tf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  scsi_10_lba_len (int const*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  scsi_16_lba_len (int const*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  scsi_6_lba_len (int const*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  unlikely (int const) ; 

__attribute__((used)) static unsigned int ata_scsi_rw_xlat(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	const u8 *cdb = scmd->cmnd;
	unsigned int tf_flags = 0;
	u64 block;
	u32 n_block;
	int rc;

	if (cdb[0] == WRITE_10 || cdb[0] == WRITE_6 || cdb[0] == WRITE_16)
		tf_flags |= ATA_TFLAG_WRITE;

	/* Calculate the SCSI LBA, transfer length and FUA. */
	switch (cdb[0]) {
	case READ_10:
	case WRITE_10:
		if (unlikely(scmd->cmd_len < 10))
			goto invalid_fld;
		scsi_10_lba_len(cdb, &block, &n_block);
		if (unlikely(cdb[1] & (1 << 3)))
			tf_flags |= ATA_TFLAG_FUA;
		break;
	case READ_6:
	case WRITE_6:
		if (unlikely(scmd->cmd_len < 6))
			goto invalid_fld;
		scsi_6_lba_len(cdb, &block, &n_block);

		/* for 6-byte r/w commands, transfer length 0
		 * means 256 blocks of data, not 0 block.
		 */
		if (!n_block)
			n_block = 256;
		break;
	case READ_16:
	case WRITE_16:
		if (unlikely(scmd->cmd_len < 16))
			goto invalid_fld;
		scsi_16_lba_len(cdb, &block, &n_block);
		if (unlikely(cdb[1] & (1 << 3)))
			tf_flags |= ATA_TFLAG_FUA;
		break;
	default:
		DPRINTK("no-byte command\n");
		goto invalid_fld;
	}

	/* Check and compose ATA command */
	if (!n_block)
		/* For 10-byte and 16-byte SCSI R/W commands, transfer
		 * length 0 means transfer 0 block of data.
		 * However, for ATA R/W commands, sector count 0 means
		 * 256 or 65536 sectors, not 0 sectors as in SCSI.
		 *
		 * WARNING: one or two older ATA drives treat 0 as 0...
		 */
		goto nothing_to_do;

	qc->flags |= ATA_QCFLAG_IO;
	qc->nbytes = n_block * scmd->device->sector_size;

	rc = ata_build_rw_tf(&qc->tf, qc->dev, block, n_block, tf_flags,
			     qc->tag);
	if (likely(rc == 0))
		return 0;

	if (rc == -ERANGE)
		goto out_of_range;
	/* treat all other errors as -EINVAL, fall through */
invalid_fld:
	ata_scsi_set_sense(scmd, ILLEGAL_REQUEST, 0x24, 0x0);
	/* "Invalid field in cbd" */
	return 1;

out_of_range:
	ata_scsi_set_sense(scmd, ILLEGAL_REQUEST, 0x21, 0x0);
	/* "Logical Block Address out of range" */
	return 1;

nothing_to_do:
	scmd->result = SAM_STAT_GOOD;
	return 1;
}