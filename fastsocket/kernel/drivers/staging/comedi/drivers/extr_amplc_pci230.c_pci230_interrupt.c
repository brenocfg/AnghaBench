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
struct comedi_device {struct comedi_subdevice* read_subdev; struct comedi_subdevice* write_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned char int_en; unsigned char ier; int intr_running; int /*<<< orphan*/  isr_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  intr_cpuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned char PCI230P2_INT_DAC ; 
 unsigned char PCI230_INT_ADC ; 
 unsigned char PCI230_INT_DISABLE ; 
 scalar_t__ PCI230_INT_SCE ; 
 scalar_t__ PCI230_INT_STAT ; 
 unsigned char PCI230_INT_ZCLK_CT1 ; 
 int /*<<< orphan*/  THISCPU ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  pci230_handle_ai (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci230_handle_ao_fifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci230_handle_ao_nofifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t pci230_interrupt(int irq, void *d)
{
	unsigned char status_int, valid_status_int;
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;
	unsigned long irqflags;

	/* Read interrupt status/enable register. */
	status_int = inb(devpriv->iobase1 + PCI230_INT_STAT);

	if (status_int == PCI230_INT_DISABLE) {
		return IRQ_NONE;
	}

	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	valid_status_int = devpriv->int_en & status_int;
	/* Disable triggered interrupts.
	 * (Only those interrupts that need re-enabling, are, later in the
	 * handler).  */
	devpriv->ier = devpriv->int_en & ~status_int;
	outb(devpriv->ier, devpriv->iobase1 + PCI230_INT_SCE);
	devpriv->intr_running = 1;
	devpriv->intr_cpuid = THISCPU;
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

	/*
	 * Check the source of interrupt and handle it.
	 * The PCI230 can cope with concurrent ADC, DAC, PPI C0 and C3
	 * interrupts.  However, at present (Comedi-0.7.60) does not allow
	 * concurrent execution of commands, instructions or a mixture of the
	 * two.
	 */

	if ((valid_status_int & PCI230_INT_ZCLK_CT1) != 0) {
		s = dev->write_subdev;
		pci230_handle_ao_nofifo(dev, s);
		comedi_event(dev, s);
	}

	if ((valid_status_int & PCI230P2_INT_DAC) != 0) {
		s = dev->write_subdev;
		pci230_handle_ao_fifo(dev, s);
		comedi_event(dev, s);
	}

	if ((valid_status_int & PCI230_INT_ADC) != 0) {
		s = dev->read_subdev;
		pci230_handle_ai(dev, s);
		comedi_event(dev, s);
	}

	/* Reenable interrupts. */
	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	if (devpriv->ier != devpriv->int_en) {
		devpriv->ier = devpriv->int_en;
		outb(devpriv->ier, devpriv->iobase1 + PCI230_INT_SCE);
	}
	devpriv->intr_running = 0;
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

	return IRQ_HANDLED;
}