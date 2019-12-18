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
struct comedi_device {scalar_t__ irq; scalar_t__ iobase; int /*<<< orphan*/  minor; } ;
struct TYPE_4__ {scalar_t__ dma_buffer; scalar_t__ dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2150_SIZE ; 
 int APD_BIT ; 
 scalar_t__ CONFIG_REG ; 
 int DPD_BIT ; 
 TYPE_2__* devpriv ; 
 TYPE_1__ driver_a2150 ; 
 int /*<<< orphan*/  free_dma (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int a2150_detach(struct comedi_device *dev)
{
	printk("comedi%d: %s: remove\n", dev->minor, driver_a2150.driver_name);

	/* only free stuff if it has been allocated by _attach */
	if (dev->iobase) {
		/*  put board in power-down mode */
		outw(APD_BIT | DPD_BIT, dev->iobase + CONFIG_REG);
		release_region(dev->iobase, A2150_SIZE);
	}

	if (dev->irq)
		free_irq(dev->irq, dev);
	if (devpriv) {
		if (devpriv->dma)
			free_dma(devpriv->dma);
		if (devpriv->dma_buffer)
			kfree(devpriv->dma_buffer);
	}

	return 0;
}