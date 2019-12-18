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
struct pci_dev {int dummy; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {unsigned int dma_mode; scalar_t__ devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int D0TIM ; 
 unsigned int D1TIM ; 
 unsigned int MDM ; 
 unsigned int UDM ; 
 unsigned int USD ; 
 unsigned int XFER_MW_DMA_0 ; 
 unsigned int XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,unsigned int,unsigned int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sch_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	unsigned int dma_mode	= adev->dma_mode;
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned int port	= adev->devno ? D1TIM : D0TIM;
	unsigned int data;

	pci_read_config_dword(dev, port, &data);
	/* see SCH datasheet page 351 */
	if (dma_mode >= XFER_UDMA_0) {
		/* enable Synchronous DMA mode */
		data |= USD;
		data &= ~UDM;
		data |= (dma_mode - XFER_UDMA_0) << 16;
	} else { /* must be MWDMA mode, since we masked SWDMA already */
		data &= ~(USD | MDM);
		data |= (dma_mode - XFER_MW_DMA_0) << 8;
	}
	pci_write_config_dword(dev, port, data);
}