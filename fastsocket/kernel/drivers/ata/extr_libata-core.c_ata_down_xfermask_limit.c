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
struct ata_device {unsigned long pio_mask; unsigned long mwdma_mask; unsigned long udma_mask; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  ATA_DNXFER_40C 132 
#define  ATA_DNXFER_DMA 131 
#define  ATA_DNXFER_FORCE_PIO 130 
#define  ATA_DNXFER_FORCE_PIO0 129 
#define  ATA_DNXFER_PIO 128 
 unsigned int ATA_DNXFER_QUIET ; 
 unsigned long ATA_MASK_MWDMA ; 
 unsigned long ATA_MASK_PIO ; 
 unsigned long ATA_MASK_UDMA ; 
 unsigned long ATA_UDMA_MASK_40C ; 
 int /*<<< orphan*/  BUG () ; 
 int ENOENT ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,char*) ; 
 char* ata_mode_string (unsigned long) ; 
 unsigned long ata_pack_xfermask (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ata_unpack_xfermask (unsigned long,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  fls (unsigned long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

int ata_down_xfermask_limit(struct ata_device *dev, unsigned int sel)
{
	char buf[32];
	unsigned long orig_mask, xfer_mask;
	unsigned long pio_mask, mwdma_mask, udma_mask;
	int quiet, highbit;

	quiet = !!(sel & ATA_DNXFER_QUIET);
	sel &= ~ATA_DNXFER_QUIET;

	xfer_mask = orig_mask = ata_pack_xfermask(dev->pio_mask,
						  dev->mwdma_mask,
						  dev->udma_mask);
	ata_unpack_xfermask(xfer_mask, &pio_mask, &mwdma_mask, &udma_mask);

	switch (sel) {
	case ATA_DNXFER_PIO:
		highbit = fls(pio_mask) - 1;
		pio_mask &= ~(1 << highbit);
		break;

	case ATA_DNXFER_DMA:
		if (udma_mask) {
			highbit = fls(udma_mask) - 1;
			udma_mask &= ~(1 << highbit);
			if (!udma_mask)
				return -ENOENT;
		} else if (mwdma_mask) {
			highbit = fls(mwdma_mask) - 1;
			mwdma_mask &= ~(1 << highbit);
			if (!mwdma_mask)
				return -ENOENT;
		}
		break;

	case ATA_DNXFER_40C:
		udma_mask &= ATA_UDMA_MASK_40C;
		break;

	case ATA_DNXFER_FORCE_PIO0:
		pio_mask &= 1;
	case ATA_DNXFER_FORCE_PIO:
		mwdma_mask = 0;
		udma_mask = 0;
		break;

	default:
		BUG();
	}

	xfer_mask &= ata_pack_xfermask(pio_mask, mwdma_mask, udma_mask);

	if (!(xfer_mask & ATA_MASK_PIO) || xfer_mask == orig_mask)
		return -ENOENT;

	if (!quiet) {
		if (xfer_mask & (ATA_MASK_MWDMA | ATA_MASK_UDMA))
			snprintf(buf, sizeof(buf), "%s:%s",
				 ata_mode_string(xfer_mask),
				 ata_mode_string(xfer_mask & ATA_MASK_PIO));
		else
			snprintf(buf, sizeof(buf), "%s",
				 ata_mode_string(xfer_mask));

		ata_dev_printk(dev, KERN_WARNING,
			       "limiting speed to %s\n", buf);
	}

	ata_unpack_xfermask(xfer_mask, &dev->pio_mask, &dev->mwdma_mask,
			    &dev->udma_mask);

	return 0;
}