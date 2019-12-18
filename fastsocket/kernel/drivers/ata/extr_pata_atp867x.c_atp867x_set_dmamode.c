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
struct pci_dev {scalar_t__ device; } ;
struct atp867x_priv {int /*<<< orphan*/  dma_mode; scalar_t__ pci66mhz; } ;
struct ata_port {struct atp867x_priv* private_data; TYPE_1__* host; } ;
struct ata_device {int dma_mode; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATP867X_IO_DMAMODE_MSTR_MASK ; 
 int ATP867X_IO_DMAMODE_MSTR_SHIFT ; 
 int ATP867X_IO_DMAMODE_SLAVE_MASK ; 
 int ATP867X_IO_DMAMODE_SLAVE_SHIFT ; 
 int ATP867X_IO_DMAMODE_UDMA_0 ; 
 int ATP867X_IO_DMAMODE_UDMA_5 ; 
 scalar_t__ PCI_DEVICE_ID_ARTOP_ATP867B ; 
 int XFER_UDMA_0 ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atp867x_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	struct atp867x_priv *dp = ap->private_data;
	u8 speed = adev->dma_mode;
	u8 b;
	u8 mode = speed - XFER_UDMA_0 + 1;

	/*
	 * Doc 6.6.9: decrease the udma mode value by 1 for safer UDMA speed
	 * on 66MHz bus
	 *   rev-A: UDMA_1~4 (5, 6 no change)
	 *   rev-B: all UDMA modes
	 *   UDMA_0 stays not to disable UDMA
	 */
	if (dp->pci66mhz && mode > ATP867X_IO_DMAMODE_UDMA_0  &&
	   (pdev->device == PCI_DEVICE_ID_ARTOP_ATP867B ||
	    mode < ATP867X_IO_DMAMODE_UDMA_5))
		mode--;

	b = ioread8(dp->dma_mode);
	if (adev->devno & 1) {
		b = (b & ~ATP867X_IO_DMAMODE_SLAVE_MASK) |
			(mode << ATP867X_IO_DMAMODE_SLAVE_SHIFT);
	} else {
		b = (b & ~ATP867X_IO_DMAMODE_MSTR_MASK) |
			(mode << ATP867X_IO_DMAMODE_MSTR_SHIFT);
	}
	iowrite8(b, dp->dma_mode);
}