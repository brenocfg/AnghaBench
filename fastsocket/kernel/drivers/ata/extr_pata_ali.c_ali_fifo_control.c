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
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ali_fifo_control(struct ata_port *ap, struct ata_device *adev, int on)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int pio_fifo = 0x54 + ap->port_no;
	u8 fifo;
	int shift = 4 * adev->devno;

	/* ATA - FIFO on set nibble to 0x05, ATAPI - FIFO off, set nibble to
	   0x00. Not all the docs agree but the behaviour we now use is the
	   one stated in the BIOS Programming Guide */

	pci_read_config_byte(pdev, pio_fifo, &fifo);
	fifo &= ~(0x0F << shift);
	fifo |= (on << shift);
	pci_write_config_byte(pdev, pio_fifo, fifo);
}