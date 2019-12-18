#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_9__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_11__ {int reg0e; int reg0f; } ;
struct TYPE_10__ {int reg10; int reg11; int reg12; } ;

/* Variables and functions */
 int const XFER_UDMA_0 ; 
 int const XFER_UDMA_2 ; 
 int get_indexed_reg (TYPE_1__*,int) ; 
 int max_dma_rate (struct pci_dev*) ; 
 TYPE_6__* mwdma_timings ; 
 int /*<<< orphan*/  set_indexed_reg (TYPE_1__*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 TYPE_3__* udma_timings ; 

__attribute__((used)) static void pdcnew_set_dma_mode(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	u8 adj			= (drive->dn & 1) ? 0x08 : 0x00;

	/*
	 * IDE core issues SETFEATURES_XFER to the drive first (thanks to
	 * IDE_HFLAG_POST_SET_MODE in ->host_flags).  PDC202xx hardware will
	 * automatically set the timing registers based on 100 MHz PLL output.
	 *
	 * As we set up the PLL to output 133 MHz for UltraDMA/133 capable
	 * chips, we must override the default register settings...
	 */
	if (max_dma_rate(dev) == 4) {
		u8 mode = speed & 0x07;

		if (speed >= XFER_UDMA_0) {
			set_indexed_reg(hwif, 0x10 + adj,
					udma_timings[mode].reg10);
			set_indexed_reg(hwif, 0x11 + adj,
					udma_timings[mode].reg11);
			set_indexed_reg(hwif, 0x12 + adj,
					udma_timings[mode].reg12);
		} else {
			set_indexed_reg(hwif, 0x0e + adj,
					mwdma_timings[mode].reg0e);
			set_indexed_reg(hwif, 0x0f + adj,
					mwdma_timings[mode].reg0f);
		}
	} else if (speed == XFER_UDMA_2) {
		/* Set tHOLD bit to 0 if using UDMA mode 2 */
		u8 tmp = get_indexed_reg(hwif, 0x10 + adj);

		set_indexed_reg(hwif, 0x10 + adj, tmp & 0x7f);
 	}
}