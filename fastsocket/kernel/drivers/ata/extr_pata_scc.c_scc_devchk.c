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
struct TYPE_2__ {int /*<<< orphan*/  (* sff_dev_select ) (struct ata_port*,unsigned int) ;} ;

/* Variables and functions */
 int in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,unsigned int) ; 

__attribute__((used)) static unsigned int scc_devchk (struct ata_port *ap,
				unsigned int device)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;
	u8 nsect, lbal;

	ap->ops->sff_dev_select(ap, device);

	out_be32(ioaddr->nsect_addr, 0x55);
	out_be32(ioaddr->lbal_addr, 0xaa);

	out_be32(ioaddr->nsect_addr, 0xaa);
	out_be32(ioaddr->lbal_addr, 0x55);

	out_be32(ioaddr->nsect_addr, 0x55);
	out_be32(ioaddr->lbal_addr, 0xaa);

	nsect = in_be32(ioaddr->nsect_addr);
	lbal = in_be32(ioaddr->lbal_addr);

	if ((nsect == 0x55) && (lbal == 0xaa))
		return 1;	/* we found a device */

	return 0;		/* nothing found */
}