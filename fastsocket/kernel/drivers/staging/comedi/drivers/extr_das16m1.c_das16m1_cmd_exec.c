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
struct comedi_device {scalar_t__ irq; scalar_t__ iobase; } ;
struct comedi_cmd {unsigned int chanlist_len; int flags; scalar_t__ start_src; scalar_t__ convert_src; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_2__ {int control_state; int /*<<< orphan*/  initial_hw_count; scalar_t__ adc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS16M1_8254_FIRST ; 
 scalar_t__ DAS16M1_CLEAR_INTR ; 
 scalar_t__ DAS16M1_CS ; 
 scalar_t__ DAS16M1_INTR_CONTROL ; 
 scalar_t__ DAS16M1_QUEUE_ADDR ; 
 scalar_t__ DAS16M1_QUEUE_DATA ; 
 int EXT_PACER ; 
 unsigned int EXT_TRIG_BIT ; 
 int INTE ; 
 int INT_PACER ; 
 int PACER_MASK ; 
 unsigned int Q_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int Q_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIG_EXT ; 
 int TRIG_ROUND_MASK ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  das16m1_set_pacer (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8254_load (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i8254_read (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int das16m1_cmd_exec(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int byte, i;

	if (dev->irq == 0) {
		comedi_error(dev, "irq required to execute comedi_cmd");
		return -1;
	}

	/* disable interrupts and internal pacer */
	devpriv->control_state &= ~INTE & ~PACER_MASK;
	outb(devpriv->control_state, dev->iobase + DAS16M1_INTR_CONTROL);

	/*  set software count */
	devpriv->adc_count = 0;
	/* Initialize lower half of hardware counter, used to determine how
	 * many samples are in fifo.  Value doesn't actually load into counter
	 * until counter's next clock (the next a/d conversion) */
	i8254_load(dev->iobase + DAS16M1_8254_FIRST, 0, 1, 0, 2);
	/* remember current reading of counter so we know when counter has
	 * actually been loaded */
	devpriv->initial_hw_count =
	    i8254_read(dev->iobase + DAS16M1_8254_FIRST, 0, 1);
	/* setup channel/gain queue */
	for (i = 0; i < cmd->chanlist_len; i++) {
		outb(i, dev->iobase + DAS16M1_QUEUE_ADDR);
		byte =
		    Q_CHAN(CR_CHAN(cmd->chanlist[i])) |
		    Q_RANGE(CR_RANGE(cmd->chanlist[i]));
		outb(byte, dev->iobase + DAS16M1_QUEUE_DATA);
	}

	/* set counter mode and counts */
	cmd->convert_arg =
	    das16m1_set_pacer(dev, cmd->convert_arg,
			      cmd->flags & TRIG_ROUND_MASK);

	/*  set control & status register */
	byte = 0;
	/* if we are using external start trigger (also board dislikes having
	 * both start and conversion triggers external simultaneously) */
	if (cmd->start_src == TRIG_EXT && cmd->convert_src != TRIG_EXT) {
		byte |= EXT_TRIG_BIT;
	}
	outb(byte, dev->iobase + DAS16M1_CS);
	/* clear interrupt bit */
	outb(0, dev->iobase + DAS16M1_CLEAR_INTR);

	/* enable interrupts and internal pacer */
	devpriv->control_state &= ~PACER_MASK;
	if (cmd->convert_src == TRIG_TIMER) {
		devpriv->control_state |= INT_PACER;
	} else {
		devpriv->control_state |= EXT_PACER;
	}
	devpriv->control_state |= INTE;
	outb(devpriv->control_state, dev->iobase + DAS16M1_INTR_CONTROL);

	return 0;
}