#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ctl_addr; } ;
struct ata_port {int /*<<< orphan*/  ctl; int /*<<< orphan*/  last_ctl; TYPE_2__ ioaddr; TYPE_1__* ops; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,int) ;} ;

/* Variables and functions */
 unsigned int ATA_DEV_NONE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ata_std_postreset (struct ata_link*,unsigned int*) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,int) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,int) ; 

void ata_sff_postreset(struct ata_link *link, unsigned int *classes)
{
	struct ata_port *ap = link->ap;

	ata_std_postreset(link, classes);

	/* is double-select really necessary? */
	if (classes[0] != ATA_DEV_NONE)
		ap->ops->sff_dev_select(ap, 1);
	if (classes[1] != ATA_DEV_NONE)
		ap->ops->sff_dev_select(ap, 0);

	/* bail out if no device is present */
	if (classes[0] == ATA_DEV_NONE && classes[1] == ATA_DEV_NONE) {
		DPRINTK("EXIT, no device\n");
		return;
	}

	/* set up device control */
	if (ap->ioaddr.ctl_addr) {
		iowrite8(ap->ctl, ap->ioaddr.ctl_addr);
		ap->last_ctl = ap->ctl;
	}
}