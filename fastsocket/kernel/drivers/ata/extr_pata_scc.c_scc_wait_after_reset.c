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
struct ata_ioports {int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; } ;
struct ata_port {TYPE_1__* ops; struct ata_ioports ioaddr; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ata_msleep (struct ata_port*,int) ; 
 int ata_sff_wait_ready (struct ata_link*,unsigned long) ; 
 int in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub3 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub4 (struct ata_port*,int) ; 

int scc_wait_after_reset(struct ata_link *link, unsigned int devmask,
			 unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ata_ioports *ioaddr = &ap->ioaddr;
	unsigned int dev0 = devmask & (1 << 0);
	unsigned int dev1 = devmask & (1 << 1);
	int rc, ret = 0;

	/* Spec mandates ">= 2ms" before checking status.  We wait
	 * 150ms, because that was the magic delay used for ATAPI
	 * devices in Hale Landis's ATADRVR, for the period of time
	 * between when the ATA command register is written, and then
	 * status is checked.  Because waiting for "a while" before
	 * checking status is fine, post SRST, we perform this magic
	 * delay here as well.
	 *
	 * Old drivers/ide uses the 2mS rule and then waits for ready.
	 */
	ata_msleep(ap, 150);

	/* always check readiness of the master device */
	rc = ata_sff_wait_ready(link, deadline);
	/* -ENODEV means the odd clown forgot the D7 pulldown resistor
	 * and TF status is 0xff, bail out on it too.
	 */
	if (rc)
		return rc;

	/* if device 1 was found in ata_devchk, wait for register
	 * access briefly, then wait for BSY to clear.
	 */
	if (dev1) {
		int i;

		ap->ops->sff_dev_select(ap, 1);

		/* Wait for register access.  Some ATAPI devices fail
		 * to set nsect/lbal after reset, so don't waste too
		 * much time on it.  We're gonna wait for !BSY anyway.
		 */
		for (i = 0; i < 2; i++) {
			u8 nsect, lbal;

			nsect = in_be32(ioaddr->nsect_addr);
			lbal = in_be32(ioaddr->lbal_addr);
			if ((nsect == 1) && (lbal == 1))
				break;
			ata_msleep(ap, 50);	/* give drive a breather */
		}

		rc = ata_sff_wait_ready(link, deadline);
		if (rc) {
			if (rc != -ENODEV)
				return rc;
			ret = rc;
		}
	}

	/* is all this really necessary? */
	ap->ops->sff_dev_select(ap, 0);
	if (dev1)
		ap->ops->sff_dev_select(ap, 1);
	if (dev0)
		ap->ops->sff_dev_select(ap, 0);

	return ret;
}