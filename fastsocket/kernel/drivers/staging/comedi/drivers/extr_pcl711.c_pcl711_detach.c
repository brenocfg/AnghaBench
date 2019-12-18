#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_device {scalar_t__ iobase; scalar_t__ irq; int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCL711_SIZE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcl711_detach(struct comedi_device *dev)
{
	printk("comedi%d: pcl711: remove\n", dev->minor);

	if (dev->irq)
		free_irq(dev->irq, dev);

	if (dev->iobase)
		release_region(dev->iobase, PCL711_SIZE);

	return 0;
}