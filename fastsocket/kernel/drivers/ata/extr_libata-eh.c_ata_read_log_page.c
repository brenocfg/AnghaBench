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
typedef  unsigned int u8 ;
struct ata_taskfile {unsigned int lbal; unsigned int nsect; unsigned int hob_nsect; int flags; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_READ_LOG_EXT ; 
 int /*<<< orphan*/  ATA_PROT_PIO ; 
 unsigned int ATA_SECT_SIZE ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_LBA48 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 

__attribute__((used)) static unsigned int ata_read_log_page(struct ata_device *dev,
				      u8 page, void *buf, unsigned int sectors)
{
	struct ata_taskfile tf;
	unsigned int err_mask;

	DPRINTK("read log page - page %d\n", page);

	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_READ_LOG_EXT;
	tf.lbal = page;
	tf.nsect = sectors;
	tf.hob_nsect = sectors >> 8;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_LBA48 | ATA_TFLAG_DEVICE;
	tf.protocol = ATA_PROT_PIO;

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_FROM_DEVICE,
				     buf, sectors * ATA_SECT_SIZE, 0);

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	return err_mask;
}