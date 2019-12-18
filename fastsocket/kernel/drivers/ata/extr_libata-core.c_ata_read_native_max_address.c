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
typedef  scalar_t__ u64 ;
struct ata_taskfile {int flags; int feature; int /*<<< orphan*/  device; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_device {int horkage; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 unsigned int AC_ERR_DEV ; 
 int ATA_ABORTED ; 
 int /*<<< orphan*/  ATA_CMD_READ_NATIVE_MAX ; 
 int /*<<< orphan*/  ATA_CMD_READ_NATIVE_MAX_EXT ; 
 int ATA_HORKAGE_HPA_SIZE ; 
 int /*<<< orphan*/  ATA_LBA ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int EACCES ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ata_id_has_lba48 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 
 scalar_t__ ata_tf_to_lba (struct ata_taskfile*) ; 
 scalar_t__ ata_tf_to_lba48 (struct ata_taskfile*) ; 

__attribute__((used)) static int ata_read_native_max_address(struct ata_device *dev, u64 *max_sectors)
{
	unsigned int err_mask;
	struct ata_taskfile tf;
	int lba48 = ata_id_has_lba48(dev->id);

	ata_tf_init(dev, &tf);

	/* always clear all address registers */
	tf.flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;

	if (lba48) {
		tf.command = ATA_CMD_READ_NATIVE_MAX_EXT;
		tf.flags |= ATA_TFLAG_LBA48;
	} else
		tf.command = ATA_CMD_READ_NATIVE_MAX;

	tf.protocol |= ATA_PROT_NODATA;
	tf.device |= ATA_LBA;

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_NONE, NULL, 0, 0);
	if (err_mask) {
		ata_dev_printk(dev, KERN_WARNING, "failed to read native "
			       "max address (err_mask=0x%x)\n", err_mask);
		if (err_mask == AC_ERR_DEV && (tf.feature & ATA_ABORTED))
			return -EACCES;
		return -EIO;
	}

	if (lba48)
		*max_sectors = ata_tf_to_lba48(&tf) + 1;
	else
		*max_sectors = ata_tf_to_lba(&tf) + 1;
	if (dev->horkage & ATA_HORKAGE_HPA_SIZE)
		(*max_sectors)--;
	return 0;
}