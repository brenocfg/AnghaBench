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
struct pci_dev {int dummy; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {int dma_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int sis_old_port_base (struct ata_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_133_early_set_dmamode (struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFER_MW_DMA_0;
	int drive_pci = sis_old_port_base(adev);
	u8 timing;
	/* Low 4 bits are timing */
	static const u8 udma_bits[]  = { 0x8F, 0x8A, 0x87, 0x85, 0x83, 0x82, 0x81};

	pci_read_config_byte(pdev, drive_pci + 1, &timing);

	if (adev->dma_mode < XFER_UDMA_0) {
		/* NOT SUPPORTED YET: NEED DATA SHEET. DITTO IN OLD DRIVER */
	} else {
		/* Bit 7 is UDMA on/off, bit 0-3 are cycle time */
		speed = adev->dma_mode - XFER_UDMA_0;
		timing &= ~0x8F;
		timing |= udma_bits[speed];
	}
	pci_write_config_byte(pdev, drive_pci + 1, timing);
}