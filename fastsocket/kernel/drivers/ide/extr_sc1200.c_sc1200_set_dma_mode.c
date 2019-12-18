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
typedef  unsigned int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ const XFER_MW_DMA_0 ; 
 scalar_t__ const XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,unsigned int,unsigned int) ; 
 unsigned short sc1200_get_pci_clock () ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc1200_set_dma_mode(ide_drive_t *drive, const u8 mode)
{
	ide_hwif_t		*hwif = drive->hwif;
	struct pci_dev		*dev = to_pci_dev(hwif->dev);
	unsigned int		reg, timings;
	unsigned short		pci_clock;
	unsigned int		basereg = hwif->channel ? 0x50 : 0x40;

	static const u32 udma_timing[3][3] = {
		{ 0x00921250, 0x00911140, 0x00911030 },
		{ 0x00932470, 0x00922260, 0x00922140 },
		{ 0x009436a1, 0x00933481, 0x00923261 },
	};

	static const u32 mwdma_timing[3][3] = {
		{ 0x00077771, 0x00012121, 0x00002020 },
		{ 0x000bbbb2, 0x00024241, 0x00013131 },
		{ 0x000ffff3, 0x00035352, 0x00015151 },
	};

	pci_clock = sc1200_get_pci_clock();

	/*
	 * Note that each DMA mode has several timings associated with it.
	 * The correct timing depends on the fast PCI clock freq.
	 */

	if (mode >= XFER_UDMA_0)
		timings =  udma_timing[pci_clock][mode - XFER_UDMA_0];
	else
		timings = mwdma_timing[pci_clock][mode - XFER_MW_DMA_0];

	if ((drive->dn & 1) == 0) {
		pci_read_config_dword(dev, basereg + 4, &reg);
		timings |= reg & 0x80000000;	/* preserve PIO format bit */
		pci_write_config_dword(dev, basereg + 4, timings);
	} else
		pci_write_config_dword(dev, basereg + 12, timings);
}