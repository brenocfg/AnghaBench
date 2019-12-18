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
struct local_info_t {int count; struct comedi_subdevice* s; struct comedi_device* dev; int /*<<< orphan*/  interrupt_mode; scalar_t__ stop; } ;
struct comedi_subdevice {TYPE_1__* async; scalar_t__ private; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {scalar_t__ convert_src; int flags; int chanlist_len; int* chanlist; scalar_t__ stop_src; int stop_arg; int scan_end_arg; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  convert_arg; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ AREF_DIFF ; 
 scalar_t__ CR_AREF (int) ; 
 int /*<<< orphan*/  CR_CHAN (int) ; 
 int /*<<< orphan*/  CR_RANGE (int) ; 
 scalar_t__ DAQP_AUX ; 
 scalar_t__ DAQP_COMMAND ; 
 int DAQP_COMMAND_ARM ; 
 int DAQP_COMMAND_FIFO_DATA ; 
 int DAQP_COMMAND_RSTF ; 
 int DAQP_COMMAND_RSTQ ; 
 scalar_t__ DAQP_CONTROL ; 
 int DAQP_CONTROL_FIFO_INT_ENABLE ; 
 int DAQP_CONTROL_PACER_5MHz ; 
 int DAQP_CONTROL_TRIGGER_CONTINUOUS ; 
 int DAQP_CONTROL_TRIGGER_INTERNAL ; 
 scalar_t__ DAQP_FIFO ; 
 int DAQP_FIFO_SIZE ; 
 scalar_t__ DAQP_PACER_HIGH ; 
 scalar_t__ DAQP_PACER_LOW ; 
 scalar_t__ DAQP_PACER_MID ; 
 scalar_t__ DAQP_SCANLIST ; 
 int DAQP_SCANLIST_CHANNEL (int /*<<< orphan*/ ) ; 
 int DAQP_SCANLIST_DIFFERENTIAL ; 
 int DAQP_SCANLIST_GAIN (int /*<<< orphan*/ ) ; 
 int DAQP_SCANLIST_START ; 
 scalar_t__ DAQP_STATUS ; 
 int DAQP_STATUS_EVENTS ; 
 int EIO ; 
 scalar_t__ TRIG_COUNT ; 
 int TRIG_ROUND_MASK ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  daqp_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int daqp_ns_to_timer (int /*<<< orphan*/ *,int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int daqp_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct local_info_t *local = (struct local_info_t *)s->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int counter = 100;
	int scanlist_start_on_every_entry;
	int threshold;

	int i;
	int v;

	if (local->stop) {
		return -EIO;
	}

	/* Stop any running conversion */
	daqp_ai_cancel(dev, s);

	outb(0, dev->iobase + DAQP_AUX);

	/* Reset scan list queue */
	outb(DAQP_COMMAND_RSTQ, dev->iobase + DAQP_COMMAND);

	/* Program pacer clock
	 *
	 * There's two modes we can operate in.  If convert_src is
	 * TRIG_TIMER, then convert_arg specifies the time between
	 * each conversion, so we program the pacer clock to that
	 * frequency and set the SCANLIST_START bit on every scanlist
	 * entry.  Otherwise, convert_src is TRIG_NOW, which means
	 * we want the fastest possible conversions, scan_begin_src
	 * is TRIG_TIMER, and scan_begin_arg specifies the time between
	 * each scan, so we program the pacer clock to this frequency
	 * and only set the SCANLIST_START bit on the first entry.
	 */

	if (cmd->convert_src == TRIG_TIMER) {
		int counter = daqp_ns_to_timer(&cmd->convert_arg,
					       cmd->flags & TRIG_ROUND_MASK);
		outb(counter & 0xff, dev->iobase + DAQP_PACER_LOW);
		outb((counter >> 8) & 0xff, dev->iobase + DAQP_PACER_MID);
		outb((counter >> 16) & 0xff, dev->iobase + DAQP_PACER_HIGH);
		scanlist_start_on_every_entry = 1;
	} else {
		int counter = daqp_ns_to_timer(&cmd->scan_begin_arg,
					       cmd->flags & TRIG_ROUND_MASK);
		outb(counter & 0xff, dev->iobase + DAQP_PACER_LOW);
		outb((counter >> 8) & 0xff, dev->iobase + DAQP_PACER_MID);
		outb((counter >> 16) & 0xff, dev->iobase + DAQP_PACER_HIGH);
		scanlist_start_on_every_entry = 0;
	}

	/* Program scan list */

	for (i = 0; i < cmd->chanlist_len; i++) {

		int chanspec = cmd->chanlist[i];

		/* Program one scan list entry */

		v = DAQP_SCANLIST_CHANNEL(CR_CHAN(chanspec))
		    | DAQP_SCANLIST_GAIN(CR_RANGE(chanspec));

		if (CR_AREF(chanspec) == AREF_DIFF) {
			v |= DAQP_SCANLIST_DIFFERENTIAL;
		}

		if (i == 0 || scanlist_start_on_every_entry) {
			v |= DAQP_SCANLIST_START;
		}

		outb(v & 0xff, dev->iobase + DAQP_SCANLIST);
		outb(v >> 8, dev->iobase + DAQP_SCANLIST);
	}

	/* Now it's time to program the FIFO threshold, basically the
	 * number of samples the card will buffer before it interrupts
	 * the CPU.
	 *
	 * If we don't have a stop count, then use half the size of
	 * the FIFO (the manufacturer's recommendation).  Consider
	 * that the FIFO can hold 2K samples (4K bytes).  With the
	 * threshold set at half the FIFO size, we have a margin of
	 * error of 1024 samples.  At the chip's maximum sample rate
	 * of 100,000 Hz, the CPU would have to delay interrupt
	 * service for a full 10 milliseconds in order to lose data
	 * here (as opposed to higher up in the kernel).  I've never
	 * seen it happen.  However, for slow sample rates it may
	 * buffer too much data and introduce too much delay for the
	 * user application.
	 *
	 * If we have a stop count, then things get more interesting.
	 * If the stop count is less than the FIFO size (actually
	 * three-quarters of the FIFO size - see below), we just use
	 * the stop count itself as the threshold, the card interrupts
	 * us when that many samples have been taken, and we kill the
	 * acquisition at that point and are done.  If the stop count
	 * is larger than that, then we divide it by 2 until it's less
	 * than three quarters of the FIFO size (we always leave the
	 * top quarter of the FIFO as protection against sluggish CPU
	 * interrupt response) and use that as the threshold.  So, if
	 * the stop count is 4000 samples, we divide by two twice to
	 * get 1000 samples, use that as the threshold, take four
	 * interrupts to get our 4000 samples and are done.
	 *
	 * The algorithm could be more clever.  For example, if 81000
	 * samples are requested, we could set the threshold to 1500
	 * samples and take 54 interrupts to get 81000.  But 54 isn't
	 * a power of two, so this algorithm won't find that option.
	 * Instead, it'll set the threshold at 1266 and take 64
	 * interrupts to get 81024 samples, of which the last 24 will
	 * be discarded... but we won't get the last interrupt until
	 * they've been collected.  To find the first option, the
	 * computer could look at the prime decomposition of the
	 * sample count (81000 = 3^4 * 5^3 * 2^3) and factor it into a
	 * threshold (1500 = 3 * 5^3 * 2^2) and an interrupt count (54
	 * = 3^3 * 2).  Hmmm... a one-line while loop or prime
	 * decomposition of integers... I'll leave it the way it is.
	 *
	 * I'll also note a mini-race condition before ignoring it in
	 * the code.  Let's say we're taking 4000 samples, as before.
	 * After 1000 samples, we get an interrupt.  But before that
	 * interrupt is completely serviced, another sample is taken
	 * and loaded into the FIFO.  Since the interrupt handler
	 * empties the FIFO before returning, it will read 1001 samples.
	 * If that happens four times, we'll end up taking 4004 samples,
	 * not 4000.  The interrupt handler will discard the extra four
	 * samples (by halting the acquisition with four samples still
	 * in the FIFO), but we will have to wait for them.
	 *
	 * In short, this code works pretty well, but for either of
	 * the two reasons noted, might end up waiting for a few more
	 * samples than actually requested.  Shouldn't make too much
	 * of a difference.
	 */

	/* Save away the number of conversions we should perform, and
	 * compute the FIFO threshold (in bytes, not samples - that's
	 * why we multiple local->count by 2 = sizeof(sample))
	 */

	if (cmd->stop_src == TRIG_COUNT) {
		local->count = cmd->stop_arg * cmd->scan_end_arg;
		threshold = 2 * local->count;
		while (threshold > DAQP_FIFO_SIZE * 3 / 4)
			threshold /= 2;
	} else {
		local->count = -1;
		threshold = DAQP_FIFO_SIZE / 2;
	}

	/* Reset data FIFO (see page 28 of DAQP User's Manual) */

	outb(DAQP_COMMAND_RSTF, dev->iobase + DAQP_COMMAND);

	/* Set FIFO threshold.  First two bytes are near-empty
	 * threshold, which is unused; next two bytes are near-full
	 * threshold.  We computed the number of bytes we want in the
	 * FIFO when the interrupt is generated, what the card wants
	 * is actually the number of available bytes left in the FIFO
	 * when the interrupt is to happen.
	 */

	outb(0x00, dev->iobase + DAQP_FIFO);
	outb(0x00, dev->iobase + DAQP_FIFO);

	outb((DAQP_FIFO_SIZE - threshold) & 0xff, dev->iobase + DAQP_FIFO);
	outb((DAQP_FIFO_SIZE - threshold) >> 8, dev->iobase + DAQP_FIFO);

	/* Set trigger */

	v = DAQP_CONTROL_TRIGGER_CONTINUOUS | DAQP_CONTROL_TRIGGER_INTERNAL
	    | DAQP_CONTROL_PACER_5MHz | DAQP_CONTROL_FIFO_INT_ENABLE;

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

	local->interrupt_mode = buffer;
	local->dev = dev;
	local->s = s;

	/* Start conversion */
	outb(DAQP_COMMAND_ARM | DAQP_COMMAND_FIFO_DATA,
	     dev->iobase + DAQP_COMMAND);

	return 0;
}