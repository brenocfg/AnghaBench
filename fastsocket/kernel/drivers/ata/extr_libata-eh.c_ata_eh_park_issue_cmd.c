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
struct ata_taskfile {int feature; int lbal; int lbam; int lbah; int flags; int /*<<< orphan*/  protocol; int /*<<< orphan*/  command; } ;
struct ata_eh_context {int unloaded_mask; } ;
struct ata_device {int devno; TYPE_1__* link; } ;
struct TYPE_2__ {struct ata_eh_context eh_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_CHK_POWER ; 
 int /*<<< orphan*/  ATA_CMD_IDLEIMMEDIATE ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int ATA_TFLAG_DEVICE ; 
 int ATA_TFLAG_ISADDR ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_tf_init (struct ata_device*,struct ata_taskfile*) ; 

__attribute__((used)) static void ata_eh_park_issue_cmd(struct ata_device *dev, int park)
{
	struct ata_eh_context *ehc = &dev->link->eh_context;
	struct ata_taskfile tf;
	unsigned int err_mask;

	ata_tf_init(dev, &tf);
	if (park) {
		ehc->unloaded_mask |= 1 << dev->devno;
		tf.command = ATA_CMD_IDLEIMMEDIATE;
		tf.feature = 0x44;
		tf.lbal = 0x4c;
		tf.lbam = 0x4e;
		tf.lbah = 0x55;
	} else {
		ehc->unloaded_mask &= ~(1 << dev->devno);
		tf.command = ATA_CMD_CHK_POWER;
	}

	tf.flags |= ATA_TFLAG_DEVICE | ATA_TFLAG_ISADDR;
	tf.protocol |= ATA_PROT_NODATA;
	err_mask = ata_exec_internal(dev, &tf, NULL, DMA_NONE, NULL, 0, 0);
	if (park && (err_mask || tf.lbal != 0xc4)) {
		ata_dev_printk(dev, KERN_ERR, "head unload failed!\n");
		ehc->unloaded_mask &= ~(1 << dev->devno);
	}
}