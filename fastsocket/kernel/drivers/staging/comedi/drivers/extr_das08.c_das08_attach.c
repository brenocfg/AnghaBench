#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct das08_private_struct {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_6__ {unsigned long pci_iobase; struct pci_dev* pdev; } ;
struct TYPE_5__ {scalar_t__ bustype; } ;
struct TYPE_4__ {unsigned long number; } ;

/* Variables and functions */
 scalar_t__ CNTRL ; 
 int CNTRL_DIR ; 
 int CNTRL_INTR ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ INTCSR ; 
 int INTR1_ENABLE ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 scalar_t__ PCI_DEVICE_ID_PCIDAS08 ; 
 int PCI_INTR_ENABLE ; 
 unsigned long PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_COMPUTERBOARDS ; 
 int alloc_private (struct comedi_device*,int) ; 
 scalar_t__ comedi_pci_enable (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int das08_common_attach (struct comedi_device*,unsigned long) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 scalar_t__ pci ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_2__* thisboard ; 

__attribute__((used)) static int das08_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	int ret;
	unsigned long iobase;
#ifdef CONFIG_COMEDI_PCI
	unsigned long pci_iobase = 0;
	struct pci_dev *pdev;
#endif

	ret = alloc_private(dev, sizeof(struct das08_private_struct));
	if (ret < 0)
		return ret;

	printk("comedi%d: das08: ", dev->minor);
	/*  deal with a pci board */
	if (thisboard->bustype == pci) {
#ifdef CONFIG_COMEDI_PCI
		if (it->options[0] || it->options[1]) {
			printk("bus %i slot %i ",
			       it->options[0], it->options[1]);
		}
		printk("\n");
		/*  find card */
		for (pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
		     pdev != NULL;
		     pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pdev)) {
			if (pdev->vendor == PCI_VENDOR_ID_COMPUTERBOARDS
			    && pdev->device == PCI_DEVICE_ID_PCIDAS08) {
				if (it->options[0] || it->options[1]) {
					if (pdev->bus->number == it->options[0]
					    && PCI_SLOT(pdev->devfn) ==
					    it->options[1]) {
						break;
					}
				} else {
					break;
				}
			}
		}
		if (!pdev) {
			printk("No pci das08 cards found\n");
			return -EIO;
		}
		devpriv->pdev = pdev;
		/*  enable PCI device and reserve I/O spaces */
		if (comedi_pci_enable(pdev, DRV_NAME)) {
			printk
			    (" Error enabling PCI device and requesting regions\n");
			return -EIO;
		}
		/*  read base addresses */
		pci_iobase = pci_resource_start(pdev, 1);
		iobase = pci_resource_start(pdev, 2);
		printk("pcibase 0x%lx  iobase 0x%lx\n", pci_iobase, iobase);
		devpriv->pci_iobase = pci_iobase;
#if 0
/* We could enable to pci-das08's interrupt here to make it possible
 * to do timed input in this driver, but there is little point since
 * conversions would have to be started by the interrupt handler
 * so you might as well use comedi_rt_timer to emulate commands
 */
		/* set source of interrupt trigger to counter2 output */
		outb(CNTRL_INTR | CNTRL_DIR, pci_iobase + CNTRL);
		/* Enable local interrupt 1 and pci interrupt */
		outw(INTR1_ENABLE | PCI_INTR_ENABLE, pci_iobase + INTCSR);
#endif
#else /* CONFIG_COMEDI_PCI */
		printk("this driver has not been built with PCI support.\n");
		return -EINVAL;
#endif /* CONFIG_COMEDI_PCI */
	} else {
		iobase = it->options[0];
	}
	printk("\n");

	return das08_common_attach(dev, iobase);
}