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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_16 ; 
 scalar_t__ const XFER_MW_DMA_0 ; 
 scalar_t__ const XFER_PIO_0 ; 
 scalar_t__ chipset_family ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_ata16_program_timings(ide_drive_t *drive, const u8 mode)
{
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	u16 t1 = 0;
	u8 drive_pci = 0x40 + drive->dn * 2;

	const u16 pio_timings[]   = { 0x000, 0x607, 0x404, 0x303, 0x301 };
	const u16 mwdma_timings[] = { 0x008, 0x302, 0x301 };

	pci_read_config_word(dev, drive_pci, &t1);

	/* clear active/recovery timings */
	t1 &= ~0x070f;
	if (mode >= XFER_MW_DMA_0) {
		if (chipset_family > ATA_16)
			t1 &= ~0x8000;	/* disable UDMA */
		t1 |= mwdma_timings[mode - XFER_MW_DMA_0];
	} else
		t1 |= pio_timings[mode - XFER_PIO_0];

	pci_write_config_word(dev, drive_pci, t1);
}