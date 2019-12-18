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
struct comedi_subdevice {int n_chan; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;
struct comedi_cmd {unsigned int start_src; unsigned int scan_begin_src; unsigned int convert_src; unsigned int scan_end_src; unsigned int stop_src; int start_arg; scalar_t__* chanlist; scalar_t__ chanlist_len; unsigned int convert_arg; scalar_t__ scan_end_arg; scalar_t__ stop_arg; int scan_begin_arg; int flags; } ;
struct TYPE_4__ {int hwver; } ;
struct TYPE_3__ {scalar_t__ min_hwver; scalar_t__ have_dio; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 void* COMBINE (int,int,int) ; 
 unsigned int CR_AREF (scalar_t__) ; 
 unsigned int CR_CHAN (scalar_t__) ; 
 int CR_EDGE ; 
 int CR_FLAGS_MASK ; 
 int CR_INVERT ; 
 unsigned int CR_RANGE (scalar_t__) ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,...) ; 
 unsigned int MAX_SPEED_AI_DIFF ; 
 unsigned int MAX_SPEED_AI_PLUS ; 
 unsigned int MAX_SPEED_AI_SE ; 
 unsigned int MIN_SPEED_AI ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_INT ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 int TRIG_ROUND_UP ; 
 int TRIG_TIMER ; 
 TYPE_2__* devpriv ; 
 unsigned int* pci230_ai_bipolar ; 
 int /*<<< orphan*/  pci230_ai_check_scan_period (struct comedi_cmd*) ; 
 int /*<<< orphan*/  pci230_ns_to_single_timer (unsigned int*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int pci230_ai_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int err = 0;
	unsigned int tmp;

	/* cmdtest tests a particular command to see if it is valid.
	 * Using the cmdtest ioctl, a user can create a valid cmd
	 * and then have it executes by the cmd ioctl.
	 *
	 * cmdtest returns 1,2,3,4,5 or 0, depending on which tests
	 * the command passes. */

	/* Step 1: make sure trigger sources are trivially valid.
	 * "invalid source" returned by comedilib to user mode process
	 * if this fails. */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW | TRIG_INT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	/* Unfortunately, we cannot trigger a scan off an external source
	 * on the PCI260 board, since it uses the PPIC0 (DIO) input, which
	 * isn't present on the PCI260.  For PCI260+ we can use the
	 * EXTTRIG/EXTCONVCLK input on pin 17 instead. */
	if ((thisboard->have_dio) || (thisboard->min_hwver > 0)) {
		cmd->scan_begin_src &= TRIG_FOLLOW | TRIG_TIMER | TRIG_INT
		    | TRIG_EXT;
	} else {
		cmd->scan_begin_src &= TRIG_FOLLOW | TRIG_TIMER | TRIG_INT;
	}
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;

	tmp = cmd->convert_src;
	cmd->convert_src &= TRIG_TIMER | TRIG_INT | TRIG_EXT;
	if (!cmd->convert_src || tmp != cmd->convert_src)
		err++;

	tmp = cmd->scan_end_src;
	cmd->scan_end_src &= TRIG_COUNT;
	if (!cmd->scan_end_src || tmp != cmd->scan_end_src)
		err++;

	tmp = cmd->stop_src;
	cmd->stop_src &= TRIG_COUNT | TRIG_NONE;
	if (!cmd->stop_src || tmp != cmd->stop_src)
		err++;

	if (err)
		return 1;

	/* Step 2: make sure trigger sources are unique and mutually compatible
	 * "source conflict" returned by comedilib to user mode process
	 * if this fails. */

	/* these tests are true if more than one _src bit is set */
	if ((cmd->start_src & (cmd->start_src - 1)) != 0)
		err++;
	if ((cmd->scan_begin_src & (cmd->scan_begin_src - 1)) != 0)
		err++;
	if ((cmd->convert_src & (cmd->convert_src - 1)) != 0)
		err++;
	if ((cmd->scan_end_src & (cmd->scan_end_src - 1)) != 0)
		err++;
	if ((cmd->stop_src & (cmd->stop_src - 1)) != 0)
		err++;

	/* If scan_begin_src is not TRIG_FOLLOW, then a monostable will be
	 * set up to generate a fixed number of timed conversion pulses. */
	if ((cmd->scan_begin_src != TRIG_FOLLOW)
	    && (cmd->convert_src != TRIG_TIMER))
		err++;

	if (err)
		return 2;

	/* Step 3: make sure arguments are trivially compatible.
	 * "invalid argument" returned by comedilib to user mode process
	 * if this fails. */

	if (cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}
#define MAX_SPEED_AI_SE		3200	/* PCI230 SE:   3200 ns => 312.5 kHz */
#define MAX_SPEED_AI_DIFF	8000	/* PCI230 DIFF: 8000 ns => 125 kHz */
#define MAX_SPEED_AI_PLUS	4000	/* PCI230+:     4000 ns => 250 kHz */
#define MIN_SPEED_AI	4294967295u	/* 4294967295ns = 4.29s */
			/*- Comedi limit due to unsigned int cmd.  Driver limit
			 * = 2^16 (16bit * counter) * 1000000ns (1kHz onboard
			 * clock) = 65.536s */

	if (cmd->convert_src == TRIG_TIMER) {
		unsigned int max_speed_ai;

		if (devpriv->hwver == 0) {
			/* PCI230 or PCI260.  Max speed depends whether
			 * single-ended or pseudo-differential. */
			if (cmd->chanlist && (cmd->chanlist_len > 0)) {
				/* Peek analogue reference of first channel. */
				if (CR_AREF(cmd->chanlist[0]) == AREF_DIFF) {
					max_speed_ai = MAX_SPEED_AI_DIFF;
				} else {
					max_speed_ai = MAX_SPEED_AI_SE;
				}
			} else {
				/* No channel list.  Assume single-ended. */
				max_speed_ai = MAX_SPEED_AI_SE;
			}
		} else {
			/* PCI230+ or PCI260+. */
			max_speed_ai = MAX_SPEED_AI_PLUS;
		}

		if (cmd->convert_arg < max_speed_ai) {
			cmd->convert_arg = max_speed_ai;
			err++;
		}
		if (cmd->convert_arg > MIN_SPEED_AI) {
			cmd->convert_arg = MIN_SPEED_AI;
			err++;
		}
	} else if (cmd->convert_src == TRIG_EXT) {
		/*
		 * external trigger
		 *
		 * convert_arg == (CR_EDGE | 0)
		 *                => trigger on +ve edge.
		 * convert_arg == (CR_EDGE | CR_INVERT | 0)
		 *                => trigger on -ve edge.
		 */
		if ((cmd->convert_arg & CR_FLAGS_MASK) != 0) {
			/* Trigger number must be 0. */
			if ((cmd->convert_arg & ~CR_FLAGS_MASK) != 0) {
				cmd->convert_arg = COMBINE(cmd->convert_arg, 0,
							   ~CR_FLAGS_MASK);
				err++;
			}
			/* The only flags allowed are CR_INVERT and CR_EDGE.
			 * CR_EDGE is required. */
			if ((cmd->convert_arg & (CR_FLAGS_MASK & ~CR_INVERT))
			    != CR_EDGE) {
				/* Set CR_EDGE, preserve CR_INVERT. */
				cmd->convert_arg =
				    COMBINE(cmd->start_arg, (CR_EDGE | 0),
					    CR_FLAGS_MASK & ~CR_INVERT);
				err++;
			}
		} else {
			/* Backwards compatibility with previous versions. */
			/* convert_arg == 0 => trigger on -ve edge. */
			/* convert_arg == 1 => trigger on +ve edge. */
			if (cmd->convert_arg > 1) {
				/* Default to trigger on +ve edge. */
				cmd->convert_arg = 1;
				err++;
			}
		}
	} else {
		if (cmd->convert_arg != 0) {
			cmd->convert_arg = 0;
			err++;
		}
	}

	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}

	if (cmd->stop_src == TRIG_NONE) {
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
	}

	if (cmd->scan_begin_src == TRIG_EXT) {
		/* external "trigger" to begin each scan
		 * scan_begin_arg==0 => use PPC0 input -> gate of CT0 -> gate
		 * of CT2 (sample convert trigger is CT2) */
		if ((cmd->scan_begin_arg & ~CR_FLAGS_MASK) != 0) {
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      ~CR_FLAGS_MASK);
			err++;
		}
		/* The only flag allowed is CR_EDGE, which is ignored. */
		if ((cmd->scan_begin_arg & CR_FLAGS_MASK & ~CR_EDGE) != 0) {
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      CR_FLAGS_MASK & ~CR_EDGE);
			err++;
		}
	} else if (cmd->scan_begin_src == TRIG_TIMER) {
		/* N.B. cmd->convert_arg is also TRIG_TIMER */
		if (!pci230_ai_check_scan_period(cmd)) {
			err++;
		}
	} else {
		if (cmd->scan_begin_arg != 0) {
			cmd->scan_begin_arg = 0;
			err++;
		}
	}

	if (err)
		return 3;

	/* Step 4: fix up any arguments.
	 * "argument conflict" returned by comedilib to user mode process
	 * if this fails. */

	if (cmd->convert_src == TRIG_TIMER) {
		tmp = cmd->convert_arg;
		pci230_ns_to_single_timer(&cmd->convert_arg,
					  cmd->flags & TRIG_ROUND_MASK);
		if (tmp != cmd->convert_arg)
			err++;
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* N.B. cmd->convert_arg is also TRIG_TIMER */
		tmp = cmd->scan_begin_arg;
		pci230_ns_to_single_timer(&cmd->scan_begin_arg,
					  cmd->flags & TRIG_ROUND_MASK);
		if (!pci230_ai_check_scan_period(cmd)) {
			/* Was below minimum required.  Round up. */
			pci230_ns_to_single_timer(&cmd->scan_begin_arg,
						  TRIG_ROUND_UP);
			pci230_ai_check_scan_period(cmd);
		}
		if (tmp != cmd->scan_begin_arg)
			err++;
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists. */

	if (cmd->chanlist && cmd->chanlist_len > 0) {
		enum {
			seq_err = 1 << 0,
			rangepair_err = 1 << 1,
			polarity_err = 1 << 2,
			aref_err = 1 << 3,
			diffchan_err = 1 << 4,
			buggy_chan0_err = 1 << 5
		};
		unsigned int errors;
		unsigned int chan, prev_chan;
		unsigned int range, prev_range;
		unsigned int polarity, prev_polarity;
		unsigned int aref, prev_aref;
		unsigned int subseq_len;
		unsigned int n;

		subseq_len = 0;
		errors = 0;
		prev_chan = prev_aref = prev_range = prev_polarity = 0;
		for (n = 0; n < cmd->chanlist_len; n++) {
			chan = CR_CHAN(cmd->chanlist[n]);
			range = CR_RANGE(cmd->chanlist[n]);
			aref = CR_AREF(cmd->chanlist[n]);
			polarity = pci230_ai_bipolar[range];
			/* Only the first half of the channels are available if
			 * differential.  (These are remapped in software.  In
			 * hardware, only the even channels are available.) */
			if ((aref == AREF_DIFF)
			    && (chan >= (s->n_chan / 2))) {
				errors |= diffchan_err;
			}
			if (n > 0) {
				/* Channel numbers must strictly increase or
				 * subsequence must repeat exactly. */
				if ((chan <= prev_chan)
				    && (subseq_len == 0)) {
					subseq_len = n;
				}
				if ((subseq_len > 0)
				    && (cmd->chanlist[n] !=
					cmd->chanlist[n % subseq_len])) {
					errors |= seq_err;
				}
				/* Channels must have same AREF. */
				if (aref != prev_aref) {
					errors |= aref_err;
				}
				/* Channel ranges must have same polarity. */
				if (polarity != prev_polarity) {
					errors |= polarity_err;
				}
				/* Single-ended channel pairs must have same
				 * range.  */
				if ((aref != AREF_DIFF)
				    && (((chan ^ prev_chan) & ~1) == 0)
				    && (range != prev_range)) {
					errors |= rangepair_err;
				}
			}
			prev_chan = chan;
			prev_range = range;
			prev_aref = aref;
			prev_polarity = polarity;
		}
		if (subseq_len == 0) {
			/* Subsequence is whole sequence. */
			subseq_len = n;
		}
		/* If channel list is a repeating subsequence, need a whole
		 * number of repeats. */
		if ((n % subseq_len) != 0) {
			errors |= seq_err;
		}
		if ((devpriv->hwver > 0) && (devpriv->hwver < 4)) {
			/*
			 * Buggy PCI230+ or PCI260+ requires channel 0 to be
			 * (first) in the sequence if the sequence contains
			 * more than one channel.  Hardware versions 1 and 2
			 * have the bug.  There is no hardware version 3.
			 *
			 * Actually, there are two firmwares that report
			 * themselves as hardware version 1 (the boards
			 * have different ADC chips with slightly different
			 * timing requirements, which was supposed to be
			 * invisible to software).  The first one doesn't
			 * seem to have the bug, but the second one
			 * does, and we can't tell them apart!
			 */
			if ((subseq_len > 1)
			    && (CR_CHAN(cmd->chanlist[0]) != 0)) {
				errors |= buggy_chan0_err;
			}
		}
		if (errors != 0) {
			err++;
			if ((errors & seq_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ai_cmdtest: "
					"channel numbers must increase or "
					"sequence must repeat exactly\n",
					dev->minor);
			}
			if ((errors & rangepair_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ai_cmdtest: "
					"single-ended channel pairs must "
					"have the same range\n", dev->minor);
			}
			if ((errors & polarity_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ai_cmdtest: "
					"channel sequence ranges must be all "
					"bipolar or all unipolar\n",
					dev->minor);
			}
			if ((errors & aref_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ai_cmdtest: "
					"channel sequence analogue references "
					"must be all the same (single-ended "
					"or differential)\n", dev->minor);
			}
			if ((errors & diffchan_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ai_cmdtest: "
					"differential channel number out of "
					"range 0 to %u\n", dev->minor,
					(s->n_chan / 2) - 1);
			}
			if ((errors & buggy_chan0_err) != 0) {
				/* Use printk instead of DPRINTK here. */
				printk("comedi: comedi%d: amplc_pci230: "
				       "ai_cmdtest: Buggy PCI230+/260+ "
				       "h/w version %u requires first channel "
				       "of multi-channel sequence to be 0 "
				       "(corrected in h/w version 4)\n",
				       dev->minor, devpriv->hwver);
			}
		}
	}

	if (err)
		return 5;

	return 0;
}