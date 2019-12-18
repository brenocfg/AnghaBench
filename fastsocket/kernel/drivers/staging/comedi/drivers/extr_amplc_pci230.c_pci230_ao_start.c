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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {int scan_begin_src; int scan_begin_arg; } ;
struct comedi_async {int /*<<< orphan*/  inttrig; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {scalar_t__ ao_scan_count; int hwver; unsigned short daccon; int /*<<< orphan*/  isr_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  ier; int /*<<< orphan*/  int_en; int /*<<< orphan*/  ao_continuous; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_CMD_STARTED ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int CR_INVERT ; 
 int /*<<< orphan*/  GAT_CONFIG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GAT_VCC ; 
 unsigned short PCI230P2_DAC_TRIG_EXTN ; 
 unsigned short PCI230P2_DAC_TRIG_EXTP ; 
 unsigned short PCI230P2_DAC_TRIG_MASK ; 
 unsigned short PCI230P2_DAC_TRIG_NONE ; 
 unsigned short PCI230P2_DAC_TRIG_SW ; 
 unsigned short PCI230P2_DAC_TRIG_Z2CT1 ; 
 int /*<<< orphan*/  PCI230P2_INT_DAC ; 
 scalar_t__ PCI230_DACCON ; 
 scalar_t__ PCI230_INT_SCE ; 
 int /*<<< orphan*/  PCI230_INT_ZCLK_CT1 ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
#define  TRIG_EXT 130 
#define  TRIG_INT 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_inttrig_scan_begin ; 
 int /*<<< orphan*/  pci230_ao_stop (struct comedi_device*,struct comedi_subdevice*) ; 
 int pci230_handle_ao_fifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pci230_ao_start(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned long irqflags;

	set_bit(AO_CMD_STARTED, &devpriv->state);
	if (!devpriv->ao_continuous && (devpriv->ao_scan_count == 0)) {
		/* An empty acquisition! */
		async->events |= COMEDI_CB_EOA;
		pci230_ao_stop(dev, s);
		comedi_event(dev, s);
	} else {
		if (devpriv->hwver >= 2) {
			/* Using DAC FIFO. */
			unsigned short scantrig;
			int run;

			/* Preload FIFO data. */
			run = pci230_handle_ao_fifo(dev, s);
			comedi_event(dev, s);
			if (!run) {
				/* Stopped. */
				return;
			}
			/* Set scan trigger source. */
			switch (cmd->scan_begin_src) {
			case TRIG_TIMER:
				scantrig = PCI230P2_DAC_TRIG_Z2CT1;
				break;
			case TRIG_EXT:
				/* Trigger on EXTTRIG/EXTCONVCLK pin. */
				if ((cmd->scan_begin_arg & CR_INVERT) == 0) {
					/* +ve edge */
					scantrig = PCI230P2_DAC_TRIG_EXTP;
				} else {
					/* -ve edge */
					scantrig = PCI230P2_DAC_TRIG_EXTN;
				}
				break;
			case TRIG_INT:
				scantrig = PCI230P2_DAC_TRIG_SW;
				break;
			default:
				/* Shouldn't get here. */
				scantrig = PCI230P2_DAC_TRIG_NONE;
				break;
			}
			devpriv->daccon = (devpriv->daccon
					   & ~PCI230P2_DAC_TRIG_MASK) |
			    scantrig;
			outw(devpriv->daccon, dev->iobase + PCI230_DACCON);

		}
		switch (cmd->scan_begin_src) {
		case TRIG_TIMER:
			if (devpriv->hwver < 2) {
				/* Not using DAC FIFO. */
				/* Enable CT1 timer interrupt. */
				spin_lock_irqsave(&devpriv->isr_spinlock,
						  irqflags);
				devpriv->int_en |= PCI230_INT_ZCLK_CT1;
				devpriv->ier |= PCI230_INT_ZCLK_CT1;
				outb(devpriv->ier,
				     devpriv->iobase1 + PCI230_INT_SCE);
				spin_unlock_irqrestore(&devpriv->isr_spinlock,
						       irqflags);
			}
			/* Set CT1 gate high to start counting. */
			outb(GAT_CONFIG(1, GAT_VCC),
			     devpriv->iobase1 + PCI230_ZGAT_SCE);
			break;
		case TRIG_INT:
			async->inttrig = pci230_ao_inttrig_scan_begin;
			break;
		}
		if (devpriv->hwver >= 2) {
			/* Using DAC FIFO.  Enable DAC FIFO interrupt. */
			spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
			devpriv->int_en |= PCI230P2_INT_DAC;
			devpriv->ier |= PCI230P2_INT_DAC;
			outb(devpriv->ier, devpriv->iobase1 + PCI230_INT_SCE);
			spin_unlock_irqrestore(&devpriv->isr_spinlock,
					       irqflags);
		}
	}
}