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
struct comedi_device {scalar_t__ subdevices; scalar_t__ irq; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {scalar_t__ pci_dev; scalar_t__ s5933_config; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 int /*<<< orphan*/  INTCSR_INBOX_INTR_STATUS ; 
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 

__attribute__((used)) static int cb_pcidas_detach(struct comedi_device *dev)
{
	printk("comedi%d: cb_pcidas: remove\n", dev->minor);

	if (devpriv) {
		if (devpriv->s5933_config) {
			/*  disable and clear interrupts on amcc s5933 */
			outl(INTCSR_INBOX_INTR_STATUS,
			     devpriv->s5933_config + AMCC_OP_REG_INTCSR);
#ifdef CB_PCIDAS_DEBUG
			printk("detaching, incsr is 0x%x\n",
			       inl(devpriv->s5933_config + AMCC_OP_REG_INTCSR));
#endif
		}
	}
	if (dev->irq)
		free_irq(dev->irq, dev);
	if (dev->subdevices)
		subdev_8255_cleanup(dev, dev->subdevices + 2);
	if (devpriv && devpriv->pci_dev) {
		if (devpriv->s5933_config) {
			comedi_pci_disable(devpriv->pci_dev);
		}
		pci_dev_put(devpriv->pci_dev);
	}

	return 0;
}