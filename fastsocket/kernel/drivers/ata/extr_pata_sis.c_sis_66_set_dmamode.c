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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {int dma_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 int sis_old_port_base (struct ata_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_66_set_dmamode (struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFER_MW_DMA_0;
	int drive_pci = sis_old_port_base(adev);
	u16 timing;

	/* MWDMA 0-2 and UDMA 0-5 */
	const u16 mwdma_bits[] = { 0x008, 0x302, 0x301 };
	const u16 udma_bits[]  = { 0xF000, 0xD000, 0xB000, 0xA000, 0x9000, 0x8000 };

	pci_read_config_word(pdev, drive_pci, &timing);

	if (adev->dma_mode < XFER_UDMA_0) {
		/* bits 3-0 hold recovery timing bits 8-10 active timing and
		   the higher bits are dependant on the device, bit 15 udma */
		timing &= ~0x870F;
		timing |= mwdma_bits[speed];
	} else {
		/* Bit 15 is UDMA on/off, bit 12-14 are cycle time */
		speed = adev->dma_mode - XFER_UDMA_0;
		timing &= ~0xF000;
		timing |= udma_bits[speed];
	}
	pci_write_config_word(pdev, drive_pci, timing);
}