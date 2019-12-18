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
struct ata_ioports {scalar_t__ ctl_addr; } ;
struct ata_port {TYPE_1__* ops; int /*<<< orphan*/  ctl; int /*<<< orphan*/  last_ctl; struct ata_ioports ioaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_irq_clear ) (struct ata_port*) ;int /*<<< orphan*/  (* sff_check_status ) (struct ata_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_NIEN ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*) ; 

void ata_sff_freeze(struct ata_port *ap)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;

	ap->ctl |= ATA_NIEN;
	ap->last_ctl = ap->ctl;

	if (ioaddr->ctl_addr)
		iowrite8(ap->ctl, ioaddr->ctl_addr);

	/* Under certain circumstances, some controllers raise IRQ on
	 * ATA_NIEN manipulation.  Also, many controllers fail to mask
	 * previously pending IRQ on ATA_NIEN assertion.  Clear it.
	 */
	ap->ops->sff_check_status(ap);

	ap->ops->sff_irq_clear(ap);
}