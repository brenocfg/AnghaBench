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
typedef  int u64 ;
typedef  int u32 ;
struct ata_taskfile {int flags; unsigned int nsect; int hob_feature; int feature; int hob_lbah; int hob_lbam; int hob_lbal; int lbah; int lbam; int lbal; int device; int hob_nsect; int /*<<< orphan*/  command; int /*<<< orphan*/  protocol; } ;
struct ata_device {int flags; int sectors; int heads; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_FPDMA_READ ; 
 int /*<<< orphan*/  ATA_CMD_FPDMA_WRITE ; 
 int ATA_DFLAG_LBA ; 
 int ATA_DFLAG_LBA48 ; 
 int ATA_LBA ; 
 int /*<<< orphan*/  ATA_PROT_NCQ ; 
 unsigned int ATA_TAG_INTERNAL ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_FUA ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA ; 
 int ATA_TFLAG_LBA48 ; 
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  DPRINTK (char*,int,int,int,int,int) ; 
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ ata_ncq_enabled (struct ata_device*) ; 
 scalar_t__ ata_rwcmd_protocol (struct ata_taskfile*,struct ata_device*) ; 
 scalar_t__ lba_28_ok (int,int) ; 
 scalar_t__ lba_48_ok (int,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

int ata_build_rw_tf(struct ata_taskfile *tf, struct ata_device *dev,
		    u64 block, u32 n_block, unsigned int tf_flags,
		    unsigned int tag)
{
	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf->flags |= tf_flags;

	if (ata_ncq_enabled(dev) && likely(tag != ATA_TAG_INTERNAL)) {
		/* yay, NCQ */
		if (!lba_48_ok(block, n_block))
			return -ERANGE;

		tf->protocol = ATA_PROT_NCQ;
		tf->flags |= ATA_TFLAG_LBA | ATA_TFLAG_LBA48;

		if (tf->flags & ATA_TFLAG_WRITE)
			tf->command = ATA_CMD_FPDMA_WRITE;
		else
			tf->command = ATA_CMD_FPDMA_READ;

		tf->nsect = tag << 3;
		tf->hob_feature = (n_block >> 8) & 0xff;
		tf->feature = n_block & 0xff;

		tf->hob_lbah = (block >> 40) & 0xff;
		tf->hob_lbam = (block >> 32) & 0xff;
		tf->hob_lbal = (block >> 24) & 0xff;
		tf->lbah = (block >> 16) & 0xff;
		tf->lbam = (block >> 8) & 0xff;
		tf->lbal = block & 0xff;

		tf->device = 1 << 6;
		if (tf->flags & ATA_TFLAG_FUA)
			tf->device |= 1 << 7;
	} else if (dev->flags & ATA_DFLAG_LBA) {
		tf->flags |= ATA_TFLAG_LBA;

		if (lba_28_ok(block, n_block)) {
			/* use LBA28 */
			tf->device |= (block >> 24) & 0xf;
		} else if (lba_48_ok(block, n_block)) {
			if (!(dev->flags & ATA_DFLAG_LBA48))
				return -ERANGE;

			/* use LBA48 */
			tf->flags |= ATA_TFLAG_LBA48;

			tf->hob_nsect = (n_block >> 8) & 0xff;

			tf->hob_lbah = (block >> 40) & 0xff;
			tf->hob_lbam = (block >> 32) & 0xff;
			tf->hob_lbal = (block >> 24) & 0xff;
		} else
			/* request too large even for LBA48 */
			return -ERANGE;

		if (unlikely(ata_rwcmd_protocol(tf, dev) < 0))
			return -EINVAL;

		tf->nsect = n_block & 0xff;

		tf->lbah = (block >> 16) & 0xff;
		tf->lbam = (block >> 8) & 0xff;
		tf->lbal = block & 0xff;

		tf->device |= ATA_LBA;
	} else {
		/* CHS */
		u32 sect, head, cyl, track;

		/* The request -may- be too large for CHS addressing. */
		if (!lba_28_ok(block, n_block))
			return -ERANGE;

		if (unlikely(ata_rwcmd_protocol(tf, dev) < 0))
			return -EINVAL;

		/* Convert LBA to CHS */
		track = (u32)block / dev->sectors;
		cyl   = track / dev->heads;
		head  = track % dev->heads;
		sect  = (u32)block % dev->sectors + 1;

		DPRINTK("block %u track %u cyl %u head %u sect %u\n",
			(u32)block, track, cyl, head, sect);

		/* Check whether the converted CHS can fit.
		   Cylinder: 0-65535
		   Head: 0-15
		   Sector: 1-255*/
		if ((cyl >> 16) || (head >> 4) || (sect >> 8) || (!sect))
			return -ERANGE;

		tf->nsect = n_block & 0xff; /* Sector count 0 means 256 sectors */
		tf->lbal = sect;
		tf->lbam = cyl;
		tf->lbah = cyl >> 8;
		tf->device |= head;
	}

	return 0;
}