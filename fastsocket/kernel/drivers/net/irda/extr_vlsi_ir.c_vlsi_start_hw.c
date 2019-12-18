#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  last_rx; int /*<<< orphan*/  rx_ring; struct pci_dev* pdev; } ;
typedef  TYPE_1__ vlsi_irda_dev_t ;
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 int IRMISC_UARTEN ; 
 int IRMISC_UARTTST ; 
 int MSTRPAGE_VALUE ; 
 int /*<<< orphan*/  VLSI_PCI_IRMISC ; 
 int /*<<< orphan*/  VLSI_PCI_MSTRPAGE ; 
 scalar_t__ VLSI_PIO_PROMPT ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlsi_fill_rx (int /*<<< orphan*/ ) ; 
 scalar_t__ vlsi_init_chip (struct pci_dev*) ; 

__attribute__((used)) static int vlsi_start_hw(vlsi_irda_dev_t *idev)
{
	struct pci_dev *pdev = idev->pdev;
	struct net_device *ndev = pci_get_drvdata(pdev);
	unsigned iobase = ndev->base_addr;
	u8 byte;

	/* we don't use the legacy UART, disable its address decoding */

	pci_read_config_byte(pdev, VLSI_PCI_IRMISC, &byte);
	byte &= ~(IRMISC_UARTEN | IRMISC_UARTTST);
	pci_write_config_byte(pdev, VLSI_PCI_IRMISC, byte);

	/* enable PCI busmaster access to our 16MB page */

	pci_write_config_byte(pdev, VLSI_PCI_MSTRPAGE, MSTRPAGE_VALUE);
	pci_set_master(pdev);

	if (vlsi_init_chip(pdev) < 0) {
		pci_disable_device(pdev);
		return -1;
	}

	vlsi_fill_rx(idev->rx_ring);

	do_gettimeofday(&idev->last_rx);	/* first mtt may start from now on */

	outw(0, iobase+VLSI_PIO_PROMPT);	/* kick hw state machine */

	return 0;
}