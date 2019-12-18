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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {scalar_t__ dma1; scalar_t__ dma0; } ;

/* Variables and functions */
 scalar_t__ DAS1800_CONTROL_A ; 
 scalar_t__ DAS1800_CONTROL_B ; 
 scalar_t__ DAS1800_STATUS ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int das1800_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	outb(0x0, dev->iobase + DAS1800_STATUS);	/* disable conversions */
	outb(0x0, dev->iobase + DAS1800_CONTROL_B);	/* disable interrupts and dma */
	outb(0x0, dev->iobase + DAS1800_CONTROL_A);	/* disable and clear fifo and stop triggering */
	if (devpriv->dma0)
		disable_dma(devpriv->dma0);
	if (devpriv->dma1)
		disable_dma(devpriv->dma1);
	return 0;
}