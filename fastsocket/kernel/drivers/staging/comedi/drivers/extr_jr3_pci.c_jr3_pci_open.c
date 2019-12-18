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
struct jr3_pci_subdev_private {int /*<<< orphan*/  channel_no; int /*<<< orphan*/  serial_no; } ;
struct jr3_pci_dev_private {int n_channels; } ;
struct comedi_device {TYPE_1__* subdevices; struct jr3_pci_dev_private* private; } ;
struct TYPE_2__ {struct jr3_pci_subdev_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void jr3_pci_open(struct comedi_device *dev)
{
	int i;
	struct jr3_pci_dev_private *devpriv = dev->private;

	printk("jr3_pci_open\n");
	for (i = 0; i < devpriv->n_channels; i++) {
		struct jr3_pci_subdev_private *p;

		p = dev->subdevices[i].private;
		if (p) {
			printk("serial: %p %d (%d)\n", p, p->serial_no,
			       p->channel_no);
		}
	}
}