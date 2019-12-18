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
typedef  unsigned long u64 ;
typedef  scalar_t__ u32 ;
struct pci_pbm_info {unsigned long ino_bitmap; TYPE_1__* op; scalar_t__ pci_last_busno; scalar_t__ pci_first_busno; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__* of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void pci_get_pbm_props(struct pci_pbm_info *pbm)
{
	const u32 *val = of_get_property(pbm->op->node, "bus-range", NULL);

	pbm->pci_first_busno = val[0];
	pbm->pci_last_busno = val[1];

	val = of_get_property(pbm->op->node, "ino-bitmap", NULL);
	if (val) {
		pbm->ino_bitmap = (((u64)val[1] << 32UL) |
				   ((u64)val[0] <<  0UL));
	}
}