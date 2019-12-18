#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct net2280 {TYPE_2__* usb; TYPE_1__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  usbctl; } ;
struct TYPE_3__ {int /*<<< orphan*/  pciirqenb1; int /*<<< orphan*/  pciirqenb0; } ;

/* Variables and functions */
 struct net2280* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void net2280_shutdown (struct pci_dev *pdev)
{
	struct net2280		*dev = pci_get_drvdata (pdev);

	/* disable IRQs */
	writel (0, &dev->regs->pciirqenb0);
	writel (0, &dev->regs->pciirqenb1);

	/* disable the pullup so the host will think we're gone */
	writel (0, &dev->usb->usbctl);
}