#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_8__ {int /*<<< orphan*/  reg13; int /*<<< orphan*/  reg0d; int /*<<< orphan*/  reg0c; } ;

/* Variables and functions */
 int max_dma_rate (struct pci_dev*) ; 
 TYPE_4__* pio_timings ; 
 int /*<<< orphan*/  set_indexed_reg (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdcnew_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	u8 adj = (drive->dn & 1) ? 0x08 : 0x00;

	if (max_dma_rate(dev) == 4) {
		set_indexed_reg(hwif, 0x0c + adj, pio_timings[pio].reg0c);
		set_indexed_reg(hwif, 0x0d + adj, pio_timings[pio].reg0d);
		set_indexed_reg(hwif, 0x13 + adj, pio_timings[pio].reg13);
	}
}