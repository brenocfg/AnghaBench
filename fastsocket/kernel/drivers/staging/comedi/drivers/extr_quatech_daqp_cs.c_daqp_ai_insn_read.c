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
struct local_info_t {int /*<<< orphan*/  eos; struct comedi_subdevice* s; struct comedi_device* dev; int /*<<< orphan*/  interrupt_mode; scalar_t__ stop; } ;
struct comedi_subdevice {scalar_t__ private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ AREF_DIFF ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAQP_AUX ; 
 scalar_t__ DAQP_COMMAND ; 
 int DAQP_COMMAND_ARM ; 
 int DAQP_COMMAND_FIFO_DATA ; 
 int DAQP_COMMAND_RSTF ; 
 int DAQP_COMMAND_RSTQ ; 
 scalar_t__ DAQP_CONTROL ; 
 int DAQP_CONTROL_EOS_INT_ENABLE ; 
 int DAQP_CONTROL_PACER_100kHz ; 
 int DAQP_CONTROL_TRIGGER_INTERNAL ; 
 int DAQP_CONTROL_TRIGGER_ONESHOT ; 
 scalar_t__ DAQP_FIFO ; 
 scalar_t__ DAQP_SCANLIST ; 
 int DAQP_SCANLIST_CHANNEL (int /*<<< orphan*/ ) ; 
 int DAQP_SCANLIST_DIFFERENTIAL ; 
 int DAQP_SCANLIST_GAIN (int /*<<< orphan*/ ) ; 
 int DAQP_SCANLIST_START ; 
 scalar_t__ DAQP_STATUS ; 
 int DAQP_STATUS_EVENTS ; 
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  daqp_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semaphore ; 

__attribute__((used)) static int daqp_ai_insn_read(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	struct local_info_t *local = (struct local_info_t *)s->private;
	int i;
	int v;
	int counter = 10000;

	if (local->stop) {
		return -EIO;
	}

	/* Stop any running conversion */
	daqp_ai_cancel(dev, s);

	outb(0, dev->iobase + DAQP_AUX);

	/* Reset scan list queue */
	outb(DAQP_COMMAND_RSTQ, dev->iobase + DAQP_COMMAND);

	/* Program one scan list entry */

	v = DAQP_SCANLIST_CHANNEL(CR_CHAN(insn->chanspec))
	    | DAQP_SCANLIST_GAIN(CR_RANGE(insn->chanspec));

	if (CR_AREF(insn->chanspec) == AREF_DIFF) {
		v |= DAQP_SCANLIST_DIFFERENTIAL;
	}

	v |= DAQP_SCANLIST_START;

	outb(v & 0xff, dev->iobase + DAQP_SCANLIST);
	outb(v >> 8, dev->iobase + DAQP_SCANLIST);

	/* Reset data FIFO (see page 28 of DAQP User's Manual) */

	outb(DAQP_COMMAND_RSTF, dev->iobase + DAQP_COMMAND);

	/* Set trigger */

	v = DAQP_CONTROL_TRIGGER_ONESHOT | DAQP_CONTROL_TRIGGER_INTERNAL
	    | DAQP_CONTROL_PACER_100kHz | DAQP_CONTROL_EOS_INT_ENABLE;

	outb(v, dev->iobase + DAQP_CONTROL);

	/* Reset any pending interrupts (my card has a tendancy to require
	 * require multiple reads on the status register to achieve this)
	 */

	while (--counter
	       && (inb(dev->iobase + DAQP_STATUS) & DAQP_STATUS_EVENTS)) ;
	if (!counter) {
		printk("daqp: couldn't clear interrupts in status register\n");
		return -1;
	}

	/* Make sure semaphore is blocked */
	sema_init(&local->eos, 0);
	local->interrupt_mode = semaphore;
	local->dev = dev;
	local->s = s;

	for (i = 0; i < insn->n; i++) {

		/* Start conversion */
		outb(DAQP_COMMAND_ARM | DAQP_COMMAND_FIFO_DATA,
		     dev->iobase + DAQP_COMMAND);

		/* Wait for interrupt service routine to unblock semaphore */
		/* Maybe could use a timeout here, but it's interruptible */
		if (down_interruptible(&local->eos))
			return -EINTR;

		data[i] = inb(dev->iobase + DAQP_FIFO);
		data[i] |= inb(dev->iobase + DAQP_FIFO) << 8;
		data[i] ^= 0x8000;
	}

	return insn->n;
}