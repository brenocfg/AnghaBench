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
struct ata_taskfile {int flags; int device; int lbah; int lbam; int lbal; scalar_t__ hob_lbal; scalar_t__ hob_lbam; scalar_t__ hob_lbah; } ;
struct ata_device {int heads; int sectors; } ;

/* Variables and functions */
 int ATA_TFLAG_LBA ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*) ; 

u64 ata_tf_read_block(struct ata_taskfile *tf, struct ata_device *dev)
{
	u64 block = 0;

	if (tf->flags & ATA_TFLAG_LBA) {
		if (tf->flags & ATA_TFLAG_LBA48) {
			block |= (u64)tf->hob_lbah << 40;
			block |= (u64)tf->hob_lbam << 32;
			block |= (u64)tf->hob_lbal << 24;
		} else
			block |= (tf->device & 0xf) << 24;

		block |= tf->lbah << 16;
		block |= tf->lbam << 8;
		block |= tf->lbal;
	} else {
		u32 cyl, head, sect;

		cyl = tf->lbam | (tf->lbah << 8);
		head = tf->device & 0xf;
		sect = tf->lbal;

		if (!sect) {
			ata_dev_printk(dev, KERN_WARNING, "device reported "
				       "invalid CHS sector 0\n");
			sect = 1; /* oh well */
		}

		block = (cyl * dev->heads + head) * dev->sectors + sect - 1;
	}

	return block;
}