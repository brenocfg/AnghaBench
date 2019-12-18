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
struct comedi_device {scalar_t__ attached; int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DAS16M1_CLEAR_INTR ; 
 scalar_t__ DAS16M1_CS ; 
 int IRQDATA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int OVRUN ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  das16m1_handler (struct comedi_device*,int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t das16m1_interrupt(int irq, void *d)
{
	int status;
	struct comedi_device *dev = d;

	if (dev->attached == 0) {
		comedi_error(dev, "premature interrupt");
		return IRQ_HANDLED;
	}
	/*  prevent race with comedi_poll() */
	spin_lock(&dev->spinlock);

	status = inb(dev->iobase + DAS16M1_CS);

	if ((status & (IRQDATA | OVRUN)) == 0) {
		comedi_error(dev, "spurious interrupt");
		spin_unlock(&dev->spinlock);
		return IRQ_NONE;
	}

	das16m1_handler(dev, status);

	/* clear interrupt */
	outb(0, dev->iobase + DAS16M1_CLEAR_INTR);

	spin_unlock(&dev->spinlock);
	return IRQ_HANDLED;
}