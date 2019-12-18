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
struct comedi_device {int /*<<< orphan*/  minor; scalar_t__ subdevices; } ;
struct TYPE_4__ {scalar_t__ attached_successfully; scalar_t__ pci_dev; scalar_t__ registers; scalar_t__ attached_to_8255; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_pci_disable (scalar_t__) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  pci_dev_put (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int detach(struct comedi_device *dev)
{
	if (devpriv) {

		if (dev->subdevices && devpriv->attached_to_8255) {
			/* de-register us from the 8255 driver */
			subdev_8255_cleanup(dev, dev->subdevices + 2);
			devpriv->attached_to_8255 = 0;
		}

		if (devpriv->pci_dev) {
			if (devpriv->registers) {
				comedi_pci_disable(devpriv->pci_dev);
			}
			pci_dev_put(devpriv->pci_dev);
		}

		if (devpriv->attached_successfully && thisboard)
			printk("comedi%d: %s: detached\n", dev->minor,
			       thisboard->name);

	}

	return 0;
}