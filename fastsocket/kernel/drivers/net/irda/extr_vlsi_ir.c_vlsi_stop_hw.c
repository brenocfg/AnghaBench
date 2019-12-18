#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; struct pci_dev* pdev; } ;
typedef  TYPE_1__ vlsi_irda_dev_t ;
struct pci_dev {int dummy; } ;
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRINTR_INT_MASK ; 
 unsigned int VLSI_PIO_IRCFG ; 
 unsigned int VLSI_PIO_IRENABLE ; 
 unsigned int VLSI_PIO_IRINTR ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vlsi_clear_regs (unsigned int) ; 
 int /*<<< orphan*/  vlsi_stop_clock (struct pci_dev*) ; 
 int /*<<< orphan*/  vlsi_unarm_rx (TYPE_1__*) ; 
 int /*<<< orphan*/  vlsi_unarm_tx (TYPE_1__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int vlsi_stop_hw(vlsi_irda_dev_t *idev)
{
	struct pci_dev *pdev = idev->pdev;
	struct net_device *ndev = pci_get_drvdata(pdev);
	unsigned iobase = ndev->base_addr;
	unsigned long flags;

	spin_lock_irqsave(&idev->lock,flags);
	outw(0, iobase+VLSI_PIO_IRENABLE);
	outw(0, iobase+VLSI_PIO_IRCFG);			/* disable everything */

	/* disable and w/c irqs */
	outb(0, iobase+VLSI_PIO_IRINTR);
	wmb();
	outb(IRINTR_INT_MASK, iobase+VLSI_PIO_IRINTR);
	spin_unlock_irqrestore(&idev->lock,flags);

	vlsi_unarm_tx(idev);
	vlsi_unarm_rx(idev);

	vlsi_clear_regs(iobase);
	vlsi_stop_clock(pdev);

	pci_disable_device(pdev);

	return 0;
}