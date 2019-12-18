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
struct comedi_device {scalar_t__ iobase; scalar_t__ irq; scalar_t__ subdevices; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {scalar_t__ has_8255; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMIO16D_SIZE ; 
 TYPE_1__* boardtype ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_atmio16d (struct comedi_device*) ; 
 int /*<<< orphan*/  subdev_8255_cleanup (struct comedi_device*,scalar_t__) ; 

__attribute__((used)) static int atmio16d_detach(struct comedi_device *dev)
{
	printk("comedi%d: atmio16d: remove\n", dev->minor);

	if (dev->subdevices && boardtype->has_8255)
		subdev_8255_cleanup(dev, dev->subdevices + 3);

	if (dev->irq)
		free_irq(dev->irq, dev);

	reset_atmio16d(dev);

	if (dev->iobase)
		release_region(dev->iobase, ATMIO16D_SIZE);

	return 0;
}