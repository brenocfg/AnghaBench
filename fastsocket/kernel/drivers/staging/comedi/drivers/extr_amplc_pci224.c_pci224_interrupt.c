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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct comedi_cmd {scalar_t__ start_src; scalar_t__ stop_src; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {unsigned char intsce; int intr_running; int /*<<< orphan*/  ao_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  intr_cpuid; } ;
struct TYPE_3__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 unsigned char PCI224_INTR_DAC ; 
 unsigned char PCI224_INTR_EXT ; 
 scalar_t__ PCI224_INT_SCE ; 
 int /*<<< orphan*/  THISCPU ; 
 scalar_t__ TRIG_EXT ; 
 TYPE_2__* devpriv ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  pci224_ao_handle_fifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci224_ao_start (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci224_ao_stop (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t pci224_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = &dev->subdevices[0];
	struct comedi_cmd *cmd;
	unsigned char intstat, valid_intstat;
	unsigned char curenab;
	int retval = 0;
	unsigned long flags;

	intstat = inb(devpriv->iobase1 + PCI224_INT_SCE) & 0x3F;
	if (intstat) {
		retval = 1;
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
		valid_intstat = devpriv->intsce & intstat;
		/* Temporarily disable interrupt sources. */
		curenab = devpriv->intsce & ~intstat;
		outb(curenab, devpriv->iobase1 + PCI224_INT_SCE);
		devpriv->intr_running = 1;
		devpriv->intr_cpuid = THISCPU;
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
		if (valid_intstat != 0) {
			cmd = &s->async->cmd;
			if (valid_intstat & PCI224_INTR_EXT) {
				devpriv->intsce &= ~PCI224_INTR_EXT;
				if (cmd->start_src == TRIG_EXT) {
					pci224_ao_start(dev, s);
				} else if (cmd->stop_src == TRIG_EXT) {
					pci224_ao_stop(dev, s);
				}
			}
			if (valid_intstat & PCI224_INTR_DAC) {
				pci224_ao_handle_fifo(dev, s);
			}
		}
		/* Reenable interrupt sources. */
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
		if (curenab != devpriv->intsce) {
			outb(devpriv->intsce,
			     devpriv->iobase1 + PCI224_INT_SCE);
		}
		devpriv->intr_running = 0;
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
	}
	return IRQ_RETVAL(retval);
}