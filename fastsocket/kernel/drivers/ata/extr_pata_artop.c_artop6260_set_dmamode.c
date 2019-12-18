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
struct ata_port {scalar_t__ port_no; TYPE_1__* host; } ;
struct ata_device {unsigned int pio_mode; scalar_t__ dma_mode; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XFER_MW_DMA_0 ; 
 unsigned int XFER_PIO_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  artop6260_load_piomode (struct ata_port*,struct ata_device*,unsigned int) ; 
 scalar_t__ clock ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,scalar_t__,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void artop6260_set_dmamode (struct ata_port *ap, struct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFER_PIO_0;
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u8 ultra;

	if (adev->dma_mode == XFER_MW_DMA_0)
		pio = 1;
	else
		pio = 4;

	/* Load the PIO timing active/recovery bits */
	artop6260_load_piomode(ap, adev, pio);

	/* Add ultra DMA bits if in UDMA mode */
	pci_read_config_byte(pdev, 0x44 + ap->port_no, &ultra);
	ultra &= ~(7 << (4  * adev->devno));	/* One nibble per drive */
	if (adev->dma_mode >= XFER_UDMA_0) {
		u8 mode = adev->dma_mode - XFER_UDMA_0 + 1 - clock;
		if (mode == 0)
			mode = 1;
		ultra |= (mode << (4 * adev->devno));
	}
	pci_write_config_byte(pdev, 0x44 + ap->port_no, ultra);
}