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
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {scalar_t__ convert_src; scalar_t__ scan_begin_src; } ;
struct TYPE_4__ {scalar_t__ intr_cpuid; int adccon; int /*<<< orphan*/  isr_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  ier; int /*<<< orphan*/  int_en; scalar_t__ intr_running; int /*<<< orphan*/  ai_stop_spinlock; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CMD_STARTED ; 
 int /*<<< orphan*/  OWNER_AICMD ; 
 scalar_t__ PCI230_ADCCON ; 
 int PCI230_ADC_FIFO_RESET ; 
 int PCI230_ADC_IM_MASK ; 
 int PCI230_ADC_IR_MASK ; 
 int PCI230_ADC_TRIG_NONE ; 
 int /*<<< orphan*/  PCI230_INT_ADC ; 
 scalar_t__ PCI230_INT_SCE ; 
 scalar_t__ THISCPU ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_TIMER ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci230_cancel_ct (struct comedi_device*,int) ; 
 int /*<<< orphan*/  put_all_resources (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pci230_ai_stop(struct comedi_device *dev,
			   struct comedi_subdevice *s)
{
	unsigned long irqflags;
	struct comedi_cmd *cmd;
	int started;

	spin_lock_irqsave(&devpriv->ai_stop_spinlock, irqflags);
	started = test_and_clear_bit(AI_CMD_STARTED, &devpriv->state);
	spin_unlock_irqrestore(&devpriv->ai_stop_spinlock, irqflags);
	if (!started) {
		return;
	}

	cmd = &s->async->cmd;
	if (cmd->convert_src == TRIG_TIMER) {
		/* Stop conversion rate generator. */
		pci230_cancel_ct(dev, 2);
	}
	if (cmd->scan_begin_src != TRIG_FOLLOW) {
		/* Stop scan period monostable. */
		pci230_cancel_ct(dev, 0);
	}

	spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	/* Disable ADC interrupt and wait for interrupt routine to finish
	 * running unless we are called from the interrupt routine. */
	devpriv->int_en &= ~PCI230_INT_ADC;
	while (devpriv->intr_running && devpriv->intr_cpuid != THISCPU) {
		spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);
		spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
	}
	if (devpriv->ier != devpriv->int_en) {
		devpriv->ier = devpriv->int_en;
		outb(devpriv->ier, devpriv->iobase1 + PCI230_INT_SCE);
	}
	spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

	/* Reset FIFO, disable FIFO and set start conversion source to none.
	 * Keep se/diff and bip/uni settings */
	devpriv->adccon = (devpriv->adccon & (PCI230_ADC_IR_MASK
					      | PCI230_ADC_IM_MASK)) |
	    PCI230_ADC_TRIG_NONE;
	outw(devpriv->adccon | PCI230_ADC_FIFO_RESET,
	     dev->iobase + PCI230_ADCCON);

	/* Release resources. */
	put_all_resources(dev, OWNER_AICMD);
}