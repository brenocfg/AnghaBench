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
struct jr3_pci_dev_private {int n_channels; scalar_t__ pci_dev; scalar_t__ pci_enabled; scalar_t__ iobase; int /*<<< orphan*/  timer; } ;
struct comedi_device {TYPE_1__* subdevices; int /*<<< orphan*/  minor; struct jr3_pci_dev_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jr3_pci_detach(struct comedi_device *dev)
{
	int i;
	struct jr3_pci_dev_private *devpriv = dev->private;

	printk("comedi%d: jr3_pci: remove\n", dev->minor);
	if (devpriv) {
		del_timer_sync(&devpriv->timer);

		if (dev->subdevices) {
			for (i = 0; i < devpriv->n_channels; i++) {
				kfree(dev->subdevices[i].private);
			}
		}

		if (devpriv->iobase) {
			iounmap((void *)devpriv->iobase);
		}
		if (devpriv->pci_enabled) {
			comedi_pci_disable(devpriv->pci_dev);
		}

		if (devpriv->pci_dev) {
			pci_dev_put(devpriv->pci_dev);
		}
	}
	return 0;
}