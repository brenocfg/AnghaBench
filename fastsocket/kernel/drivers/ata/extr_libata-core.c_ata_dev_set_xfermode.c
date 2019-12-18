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
struct ata_taskfile {int flags; int nsect; int /*<<< orphan*/  protocol; int /*<<< orphan*/  feature; int /*<<< orphan*/  command; } ;
struct ata_device {int xfer_mode; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_SET_FEATURES ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int ATA_TFLAG_POLLING ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  SETFEATURES_XFER ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ata_id_has_iordy (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 

__attribute__((used)) static unsigned int ata_dev_set_xfermode(struct ata_device *dev)
{
	struct ata_taskfile tf;
	unsigned int err_mask;

	/* set up set-features taskfile */
	DPRINTK("set features - xfer mode\n");

	/* Some controllers and ATAPI devices show flaky interrupt
	 * behavior after setting xfer mode.  Use polling instead.
	 */
	ata_tf_init(dev, &tf);
	tf.command = ATA_CMD_SET_FEATURES;
	tf.feature = SETFEATURES_XFER;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_POLLING;
	tf.protocol = ATA_PROT_NODATA;
	/* If we are using IORDY we must send the mode setting command */
	if (ata_pio_need_iordy(dev))
		tf.nsect = dev->xfer_mode;
	/* If the device has IORDY and the controller does not - turn it off */
 	else if (ata_id_has_iordy(dev->id))
		tf.nsect = 0x01;
	else /* In the ancient relic department - skip all of this */
		return 0;

	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_NONE, NULL, 0, 0);

	DPRINTK("EXIT, err_mask=%x\n", err_mask);
	return err_mask;
}