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
struct comedi_device {scalar_t__ subdevices; int /*<<< orphan*/  minor; } ;
struct TYPE_4__ {scalar_t__ pci_dev; scalar_t__ dio_reg_base; } ;
struct TYPE_3__ {int n_8255; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int pcidio_detach(struct comedi_device *dev)
{
	printk("comedi%d: cb_pcidio: remove\n", dev->minor);
	if (devpriv) {
		if (devpriv->pci_dev) {
			if (devpriv->dio_reg_base) {
				comedi_pci_disable(devpriv->pci_dev);
			}
			pci_dev_put(devpriv->pci_dev);
		}
	}
	if (dev->subdevices) {
		int i;
		for (i = 0; i < thisboard->n_8255; i++) {
			subdev_8255_cleanup(dev, dev->subdevices + i);
		}
	}
	return 0;
}