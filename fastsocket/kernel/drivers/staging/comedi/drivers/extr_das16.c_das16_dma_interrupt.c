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
struct comedi_device {scalar_t__ iobase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DAS16_INT ; 
 scalar_t__ DAS16_STATUS ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  das16_interrupt (struct comedi_device*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t das16_dma_interrupt(int irq, void *d)
{
	int status;
	struct comedi_device *dev = d;

	status = inb(dev->iobase + DAS16_STATUS);

	if ((status & DAS16_INT) == 0) {
		DEBUG_PRINT("spurious interrupt\n");
		return IRQ_NONE;
	}

	/* clear interrupt */
	outb(0x00, dev->iobase + DAS16_STATUS);
	das16_interrupt(dev);
	return IRQ_HANDLED;
}