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
struct TYPE_2__ {scalar_t__ intr_cpuid; int daccon; int /*<<< orphan*/  ao_spinlock; scalar_t__ intr_running; scalar_t__ iobase1; scalar_t__ intsce; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_CMD_STARTED ; 
 int COMBINE (int,int,int) ; 
 scalar_t__ PCI224_DACCEN ; 
 scalar_t__ PCI224_DACCON ; 
 int PCI224_DACCON_FIFOINTR_EMPTY ; 
 int PCI224_DACCON_FIFOINTR_MASK ; 
 int PCI224_DACCON_FIFORESET ; 
 int PCI224_DACCON_TRIG_MASK ; 
 int PCI224_DACCON_TRIG_SW ; 
 scalar_t__ PCI224_INT_SCE ; 
 scalar_t__ THISCPU ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci224_ao_stop(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	unsigned long flags;

	if (!test_and_clear_bit(AO_CMD_STARTED, &devpriv->state)) {
		return;
	}

	spin_lock_irqsave(&devpriv->ao_spinlock, flags);
	/* Kill the interrupts. */
	devpriv->intsce = 0;
	outb(0, devpriv->iobase1 + PCI224_INT_SCE);
	/*
	 * Interrupt routine may or may not be running.  We may or may not
	 * have been called from the interrupt routine (directly or
	 * indirectly via a comedi_events() callback routine).  It's highly
	 * unlikely that we've been called from some other interrupt routine
	 * but who knows what strange things coders get up to!
	 *
	 * If the interrupt routine is currently running, wait for it to
	 * finish, unless we appear to have been called via the interrupt
	 * routine.
	 */
	while (devpriv->intr_running && devpriv->intr_cpuid != THISCPU) {
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
	}
	spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
	/* Reconfigure DAC for insn_write usage. */
	outw(0, dev->iobase + PCI224_DACCEN);	/* Disable channels. */
	devpriv->daccon = COMBINE(devpriv->daccon,
				  PCI224_DACCON_TRIG_SW |
				  PCI224_DACCON_FIFOINTR_EMPTY,
				  PCI224_DACCON_TRIG_MASK |
				  PCI224_DACCON_FIFOINTR_MASK);
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);
}