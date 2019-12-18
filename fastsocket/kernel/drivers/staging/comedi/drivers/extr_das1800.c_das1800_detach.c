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
struct comedi_device {int /*<<< orphan*/  minor; scalar_t__ private; scalar_t__ irq; scalar_t__ iobase; } ;
struct TYPE_4__ {scalar_t__ ai_buf1; scalar_t__ ai_buf0; scalar_t__ dma1; scalar_t__ dma0; scalar_t__ iobase2; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAS1800_SIZE ; 
 TYPE_2__* devpriv ; 
 TYPE_1__ driver_das1800 ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int das1800_detach(struct comedi_device *dev)
{
	/* only free stuff if it has been allocated by _attach */
	if (dev->iobase)
		release_region(dev->iobase, DAS1800_SIZE);
	if (dev->irq)
		free_irq(dev->irq, dev);
	if (dev->private) {
		if (devpriv->iobase2)
			release_region(devpriv->iobase2, DAS1800_SIZE);
		if (devpriv->dma0)
			free_dma(devpriv->dma0);
		if (devpriv->dma1)
			free_dma(devpriv->dma1);
		if (devpriv->ai_buf0)
			kfree(devpriv->ai_buf0);
		if (devpriv->ai_buf1)
			kfree(devpriv->ai_buf1);
	}

	printk("comedi%d: %s: remove\n", dev->minor,
	       driver_das1800.driver_name);

	return 0;
}