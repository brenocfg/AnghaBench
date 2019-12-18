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
struct comedi_device {scalar_t__ irq; scalar_t__ iobase; scalar_t__ subdevices; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {scalar_t__ bustype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO24_SIZE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 scalar_t__ pcmcia_bustype ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int dio24_detach(struct comedi_device *dev)
{
	printk("comedi%d: ni_daq_dio24: remove\n", dev->minor);

	if (dev->subdevices)
		subdev_8255_cleanup(dev, dev->subdevices + 0);

	if (thisboard->bustype != pcmcia_bustype && dev->iobase)
		release_region(dev->iobase, DIO24_SIZE);
	if (dev->irq)
		free_irq(dev->irq, dev);

	return 0;
}