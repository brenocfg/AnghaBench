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
struct scsi_cmnd {int* cmnd; scalar_t__ sc_data_direction; TYPE_1__* device; } ;
struct ata_taskfile {scalar_t__ protocol; int hob_feature; int hob_nsect; int hob_lbal; int hob_lbam; int hob_lbah; int flags; int feature; int nsect; int lbal; int lbam; int lbah; int device; int command; } ;
struct ata_queued_cmd {int flags; int /*<<< orphan*/  sect_size; struct ata_device* dev; struct scsi_cmnd* scsicmd; struct ata_taskfile tf; } ;
struct ata_device {scalar_t__ dma_mode; unsigned int multi_count; scalar_t__ devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  sector_size; } ;

/* Variables and functions */
 int const ATA_16 ; 
#define  ATA_CMD_CFA_TRANS_SECT 159 
#define  ATA_CMD_CFA_WRITE_MULT_NE 158 
#define  ATA_CMD_CFA_WRITE_NE 157 
#define  ATA_CMD_FPDMA_READ 156 
#define  ATA_CMD_FPDMA_WRITE 155 
#define  ATA_CMD_PIO_READ 154 
#define  ATA_CMD_PIO_READ_EXT 153 
#define  ATA_CMD_PIO_WRITE 152 
#define  ATA_CMD_PIO_WRITE_EXT 151 
#define  ATA_CMD_READ 150 
#define  ATA_CMD_READ_EXT 149 
#define  ATA_CMD_READ_LONG 148 
#define  ATA_CMD_READ_LONG_ONCE 147 
#define  ATA_CMD_READ_MULTI 146 
#define  ATA_CMD_READ_MULTI_EXT 145 
#define  ATA_CMD_READ_QUEUED 144 
#define  ATA_CMD_READ_STREAM_DMA_EXT 143 
#define  ATA_CMD_READ_STREAM_EXT 142 
 int ATA_CMD_SET_FEATURES ; 
#define  ATA_CMD_VERIFY 141 
#define  ATA_CMD_VERIFY_EXT 140 
#define  ATA_CMD_WRITE 139 
#define  ATA_CMD_WRITE_EXT 138 
#define  ATA_CMD_WRITE_FUA_EXT 137 
#define  ATA_CMD_WRITE_LONG 136 
#define  ATA_CMD_WRITE_LONG_ONCE 135 
#define  ATA_CMD_WRITE_MULTI 134 
#define  ATA_CMD_WRITE_MULTI_EXT 133 
#define  ATA_CMD_WRITE_MULTI_FUA_EXT 132 
#define  ATA_CMD_WRITE_QUEUED 131 
#define  ATA_CMD_WRITE_QUEUED_FUA_EXT 130 
#define  ATA_CMD_WRITE_STREAM_DMA_EXT 129 
#define  ATA_CMD_WRITE_STREAM_EXT 128 
 int ATA_DEV1 ; 
 scalar_t__ ATA_PROT_DMA ; 
 scalar_t__ ATA_PROT_PIO ; 
 scalar_t__ ATA_PROT_UNKNOWN ; 
 int ATA_QCFLAG_QUIET ; 
 int ATA_QCFLAG_RESULT_TF ; 
 int /*<<< orphan*/  ATA_SECT_SIZE ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int ATA_TFLAG_WRITE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int SETFEATURES_XFER ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  ata_qc_set_pc_nbytes (struct ata_queued_cmd*) ; 
 scalar_t__ ata_scsi_map_proto (int const) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ is_multi_taskfile (struct ata_taskfile*) ; 
 int /*<<< orphan*/  libata_allow_tpm ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 

__attribute__((used)) static unsigned int ata_scsi_pass_thru(struct ata_queued_cmd *qc)
{
	struct ata_taskfile *tf = &(qc->tf);
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct ata_device *dev = qc->dev;
	const u8 *cdb = scmd->cmnd;

	if ((tf->protocol = ata_scsi_map_proto(cdb[1])) == ATA_PROT_UNKNOWN)
		goto invalid_fld;

	/*
	 * 12 and 16 byte CDBs use different offsets to
	 * provide the various register values.
	 */
	if (cdb[0] == ATA_16) {
		/*
		 * 16-byte CDB - may contain extended commands.
		 *
		 * If that is the case, copy the upper byte register values.
		 */
		if (cdb[1] & 0x01) {
			tf->hob_feature = cdb[3];
			tf->hob_nsect = cdb[5];
			tf->hob_lbal = cdb[7];
			tf->hob_lbam = cdb[9];
			tf->hob_lbah = cdb[11];
			tf->flags |= ATA_TFLAG_LBA48;
		} else
			tf->flags &= ~ATA_TFLAG_LBA48;

		/*
		 * Always copy low byte, device and command registers.
		 */
		tf->feature = cdb[4];
		tf->nsect = cdb[6];
		tf->lbal = cdb[8];
		tf->lbam = cdb[10];
		tf->lbah = cdb[12];
		tf->device = cdb[13];
		tf->command = cdb[14];
	} else {
		/*
		 * 12-byte CDB - incapable of extended commands.
		 */
		tf->flags &= ~ATA_TFLAG_LBA48;

		tf->feature = cdb[3];
		tf->nsect = cdb[4];
		tf->lbal = cdb[5];
		tf->lbam = cdb[6];
		tf->lbah = cdb[7];
		tf->device = cdb[8];
		tf->command = cdb[9];
	}

	/* enforce correct master/slave bit */
	tf->device = dev->devno ?
		tf->device | ATA_DEV1 : tf->device & ~ATA_DEV1;

	switch (tf->command) {
	/* READ/WRITE LONG use a non-standard sect_size */
	case ATA_CMD_READ_LONG:
	case ATA_CMD_READ_LONG_ONCE:
	case ATA_CMD_WRITE_LONG:
	case ATA_CMD_WRITE_LONG_ONCE:
		if (tf->protocol != ATA_PROT_PIO || tf->nsect != 1)
			goto invalid_fld;
		qc->sect_size = scsi_bufflen(scmd);
		break;

	/* commands using reported Logical Block size (e.g. 512 or 4K) */
	case ATA_CMD_CFA_WRITE_NE:
	case ATA_CMD_CFA_TRANS_SECT:
	case ATA_CMD_CFA_WRITE_MULT_NE:
	/* XXX: case ATA_CMD_CFA_WRITE_SECTORS_WITHOUT_ERASE: */
	case ATA_CMD_READ:
	case ATA_CMD_READ_EXT:
	case ATA_CMD_READ_QUEUED:
	/* XXX: case ATA_CMD_READ_QUEUED_EXT: */
	case ATA_CMD_FPDMA_READ:
	case ATA_CMD_READ_MULTI:
	case ATA_CMD_READ_MULTI_EXT:
	case ATA_CMD_PIO_READ:
	case ATA_CMD_PIO_READ_EXT:
	case ATA_CMD_READ_STREAM_DMA_EXT:
	case ATA_CMD_READ_STREAM_EXT:
	case ATA_CMD_VERIFY:
	case ATA_CMD_VERIFY_EXT:
	case ATA_CMD_WRITE:
	case ATA_CMD_WRITE_EXT:
	case ATA_CMD_WRITE_FUA_EXT:
	case ATA_CMD_WRITE_QUEUED:
	case ATA_CMD_WRITE_QUEUED_FUA_EXT:
	case ATA_CMD_FPDMA_WRITE:
	case ATA_CMD_WRITE_MULTI:
	case ATA_CMD_WRITE_MULTI_EXT:
	case ATA_CMD_WRITE_MULTI_FUA_EXT:
	case ATA_CMD_PIO_WRITE:
	case ATA_CMD_PIO_WRITE_EXT:
	case ATA_CMD_WRITE_STREAM_DMA_EXT:
	case ATA_CMD_WRITE_STREAM_EXT:
		qc->sect_size = scmd->device->sector_size;
		break;

	/* Everything else uses 512 byte "sectors" */
	default:
		qc->sect_size = ATA_SECT_SIZE;
	}

	/*
	 * Set flags so that all registers will be written, pass on
	 * write indication (used for PIO/DMA setup), result TF is
	 * copied back and we don't whine too much about its failure.
	 */
	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	if (scmd->sc_data_direction == DMA_TO_DEVICE)
		tf->flags |= ATA_TFLAG_WRITE;

	qc->flags |= ATA_QCFLAG_RESULT_TF | ATA_QCFLAG_QUIET;

	/*
	 * Set transfer length.
	 *
	 * TODO: find out if we need to do more here to
	 *       cover scatter/gather case.
	 */
	ata_qc_set_pc_nbytes(qc);

	/* We may not issue DMA commands if no DMA mode is set */
	if (tf->protocol == ATA_PROT_DMA && dev->dma_mode == 0)
		goto invalid_fld;

	/* sanity check for pio multi commands */
	if ((cdb[1] & 0xe0) && !is_multi_taskfile(tf))
		goto invalid_fld;

	if (is_multi_taskfile(tf)) {
		unsigned int multi_count = 1 << (cdb[1] >> 5);

		/* compare the passed through multi_count
		 * with the cached multi_count of libata
		 */
		if (multi_count != dev->multi_count)
			ata_dev_printk(dev, KERN_WARNING,
				       "invalid multi_count %u ignored\n",
				       multi_count);
	}

	/*
	 * Filter SET_FEATURES - XFER MODE command -- otherwise,
	 * SET_FEATURES - XFER MODE must be preceded/succeeded
	 * by an update to hardware-specific registers for each
	 * controller (i.e. the reason for ->set_piomode(),
	 * ->set_dmamode(), and ->post_set_mode() hooks).
	 */
	if (tf->command == ATA_CMD_SET_FEATURES &&
	    tf->feature == SETFEATURES_XFER)
		goto invalid_fld;

	/*
	 * Filter TPM commands by default. These provide an
	 * essentially uncontrolled encrypted "back door" between
	 * applications and the disk. Set libata.allow_tpm=1 if you
	 * have a real reason for wanting to use them. This ensures
	 * that installed software cannot easily mess stuff up without
	 * user intent. DVR type users will probably ship with this enabled
	 * for movie content management.
	 *
	 * Note that for ATA8 we can issue a DCS change and DCS freeze lock
	 * for this and should do in future but that it is not sufficient as
	 * DCS is an optional feature set. Thus we also do the software filter
	 * so that we comply with the TC consortium stated goal that the user
	 * can turn off TC features of their system.
	 */
	if (tf->command >= 0x5C && tf->command <= 0x5F && !libata_allow_tpm)
		goto invalid_fld;

	return 0;

 invalid_fld:
	ata_scsi_set_sense(scmd, ILLEGAL_REQUEST, 0x24, 0x00);
	/* "Invalid field in cdb" */
	return 1;
}