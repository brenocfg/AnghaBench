#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int const XFER_MW_DMA_0 ; 
 int const XFER_PIO_0 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_ata100_program_timings(ide_drive_t *drive, const u8 mode)
{
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	u8 t1, drive_pci = 0x40 + drive->dn * 2;

	/* timing bits: 7:4 active 3:0 recovery */
	const u8 pio_timings[]   = { 0x00, 0x67, 0x44, 0x33, 0x31 };
	const u8 mwdma_timings[] = { 0x08, 0x32, 0x31 };

	if (mode >= XFER_MW_DMA_0) {
		u8 t2 = 0;

		pci_read_config_byte(dev, drive_pci, &t2);
		t2 &= ~0x80;	/* disable UDMA */
		pci_write_config_byte(dev, drive_pci, t2);

		t1 = mwdma_timings[mode - XFER_MW_DMA_0];
	} else
		t1 = pio_timings[mode - XFER_PIO_0];

	pci_write_config_byte(dev, drive_pci + 1, t1);
}