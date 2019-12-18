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
struct ata_link {int pmp; int hw_sata_spd_limit; int flags; TYPE_1__* ap; } ;
struct TYPE_4__ {int spd_limit; int lflags; int /*<<< orphan*/  name; } ;
struct ata_force_ent {int port; int device; TYPE_2__ param; } ;
struct TYPE_3__ {int print_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 struct ata_force_ent* ata_force_tbl ; 
 int ata_force_tbl_size ; 
 scalar_t__ ata_is_host_link (struct ata_link*) ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void ata_force_link_limits(struct ata_link *link)
{
	bool did_spd = false;
	int linkno = link->pmp;
	int i;

	if (ata_is_host_link(link))
		linkno += 15;

	for (i = ata_force_tbl_size - 1; i >= 0; i--) {
		const struct ata_force_ent *fe = &ata_force_tbl[i];

		if (fe->port != -1 && fe->port != link->ap->print_id)
			continue;

		if (fe->device != -1 && fe->device != linkno)
			continue;

		/* only honor the first spd limit */
		if (!did_spd && fe->param.spd_limit) {
			link->hw_sata_spd_limit = (1 << fe->param.spd_limit) - 1;
			ata_link_printk(link, KERN_NOTICE,
					"FORCE: PHY spd limit set to %s\n",
					fe->param.name);
			did_spd = true;
		}

		/* let lflags stack */
		if (fe->param.lflags) {
			link->flags |= fe->param.lflags;
			ata_link_printk(link, KERN_NOTICE,
					"FORCE: link flag 0x%x forced -> 0x%x\n",
					fe->param.lflags, link->flags);
		}
	}
}