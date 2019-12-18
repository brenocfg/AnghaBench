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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int dma_mode; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_133_set_dmamode (struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFER_MW_DMA_0;
	int port = 0x40;
	u32 t1;
	u32 reg54;

	/* bits 4- cycle time 8 - cvs time */
	static const u32 timing_u100[] = { 0x6B0, 0x470, 0x350, 0x140, 0x120, 0x110, 0x000 };
	static const u32 timing_u133[] = { 0x9F0, 0x6A0, 0x470, 0x250, 0x230, 0x220, 0x210 };

	/* If bit 14 is set then the registers are mapped at 0x70 not 0x40 */
	pci_read_config_dword(pdev, 0x54, &reg54);
	if (reg54 & 0x40000000)
		port = 0x70;
	port += (8 * ap->port_no) +  (4 * adev->devno);

	pci_read_config_dword(pdev, port, &t1);

	if (adev->dma_mode < XFER_UDMA_0) {
		t1 &= ~0x00000004;
		/* FIXME: need data sheet to add MWDMA here. Also lacking on
		   ide/pci driver */
	} else {
		speed = adev->dma_mode - XFER_UDMA_0;
		/* if & 8 no UDMA133 - need info for ... */
		t1 &= ~0x00000FF0;
		t1 |= 0x00000004;
		if (t1 & 0x08)
			t1 |= timing_u133[speed];
		else
			t1 |= timing_u100[speed];
	}
	pci_write_config_dword(pdev, port, t1);
}