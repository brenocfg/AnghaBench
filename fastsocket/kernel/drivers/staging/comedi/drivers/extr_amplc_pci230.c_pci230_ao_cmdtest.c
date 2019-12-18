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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;
struct comedi_cmd {unsigned int start_src; unsigned int scan_begin_src; unsigned int convert_src; unsigned int scan_end_src; unsigned int stop_src; scalar_t__ start_arg; int scan_begin_arg; scalar_t__ scan_end_arg; scalar_t__ chanlist_len; scalar_t__ stop_arg; int flags; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_4__ {int hwver; } ;
struct TYPE_3__ {scalar_t__ min_hwver; } ;

/* Variables and functions */
 void* COMBINE (int,int /*<<< orphan*/ ,int) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_EDGE ; 
 int CR_FLAGS_MASK ; 
 int CR_INVERT ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int MAX_SPEED_AO ; 
 int MIN_SPEED_AO ; 
 int TRIG_COUNT ; 
#define  TRIG_EXT 129 
 int TRIG_INT ; 
 int TRIG_NONE ; 
 unsigned int TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
#define  TRIG_TIMER 128 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  pci230_ns_to_single_timer (unsigned int*,int) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int pci230_ao_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int err = 0;
	unsigned int tmp;

	/* cmdtest tests a particular command to see if it is valid.
	 * Using the cmdtest ioctl, a user can create a valid cmd
	 * and then have it executes by the cmd ioctl.
	 *
	 * cmdtest returns 1,2,3,4 or 0, depending on which tests
	 * the command passes. */

	/* Step 1: make sure trigger sources are trivially valid.
	 * "invalid source" returned by comedilib to user mode process
	 * if this fails. */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_INT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	if ((thisboard->min_hwver > 0) && (devpriv->hwver >= 2)) {
		/*
		 * For PCI230+ hardware version 2 onwards, allow external
		 * trigger from EXTTRIG/EXTCONVCLK input (PCI230+ pin 25).
		 *
		 * FIXME: The permitted scan_begin_src values shouldn't depend
		 * on devpriv->hwver (the detected card's actual hardware
		 * version).  They should only depend on thisboard->min_hwver
		 * (the static capabilities of the configured card).  To fix
		 * it, a new card model, e.g. "pci230+2" would have to be
		 * defined with min_hwver set to 2.  It doesn't seem worth it
		 * for this alone.  At the moment, please consider
		 * scan_begin_src==TRIG_EXT support to be a bonus rather than a
		 * guarantee!
		 */
		cmd->scan_begin_src &= TRIG_TIMER | TRIG_INT | TRIG_EXT;
	} else {
		cmd->scan_begin_src &= TRIG_TIMER | TRIG_INT;
	}
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;

	tmp = cmd->convert_src;
	cmd->convert_src &= TRIG_NOW;
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

	if (err)
		return 2;

	/* Step 3: make sure arguments are trivially compatible.
	 * "invalid argument" returned by comedilib to user mode process
	 * if this fails. */

	if (cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}
#define MAX_SPEED_AO	8000	/* 8000 ns => 125 kHz */
#define MIN_SPEED_AO	4294967295u	/* 4294967295ns = 4.29s */
			/*- Comedi limit due to unsigned int cmd.  Driver limit
			 * = 2^16 (16bit * counter) * 1000000ns (1kHz onboard
			 * clock) = 65.536s */

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		if (cmd->scan_begin_arg < MAX_SPEED_AO) {
			cmd->scan_begin_arg = MAX_SPEED_AO;
			err++;
		}
		if (cmd->scan_begin_arg > MIN_SPEED_AO) {
			cmd->scan_begin_arg = MIN_SPEED_AO;
			err++;
		}
		break;
	case TRIG_EXT:
		/* External trigger - for PCI230+ hardware version 2 onwards. */
		/* Trigger number must be 0. */
		if ((cmd->scan_begin_arg & ~CR_FLAGS_MASK) != 0) {
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      ~CR_FLAGS_MASK);
			err++;
		}
		/* The only flags allowed are CR_EDGE and CR_INVERT.  The
		 * CR_EDGE flag is ignored. */
		if ((cmd->scan_begin_arg
		     & (CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT))) != 0) {
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0,
				    CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT));
			err++;
		}
		break;
	default:
		if (cmd->scan_begin_arg != 0) {
			cmd->scan_begin_arg = 0;
			err++;
		}
		break;
	}

	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}
	if (cmd->stop_src == TRIG_NONE) {
		/* TRIG_NONE */
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
	}

	if (err)
		return 3;

	/* Step 4: fix up any arguments.
	 * "argument conflict" returned by comedilib to user mode process
	 * if this fails. */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		tmp = cmd->scan_begin_arg;
		pci230_ns_to_single_timer(&cmd->scan_begin_arg,
					  cmd->flags & TRIG_ROUND_MASK);
		if (tmp != cmd->scan_begin_arg)
			err++;
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists. */

	if (cmd->chanlist && cmd->chanlist_len > 0) {
		enum {
			seq_err = (1 << 0),
			range_err = (1 << 1)
		};
		unsigned int errors;
		unsigned int n;
		unsigned int chan, prev_chan;
		unsigned int range, first_range;

		prev_chan = CR_CHAN(cmd->chanlist[0]);
		first_range = CR_RANGE(cmd->chanlist[0]);
		errors = 0;
		for (n = 1; n < cmd->chanlist_len; n++) {
			chan = CR_CHAN(cmd->chanlist[n]);
			range = CR_RANGE(cmd->chanlist[n]);
			/* Channel numbers must strictly increase. */
			if (chan < prev_chan) {
				errors |= seq_err;
			}
			/* Ranges must be the same. */
			if (range != first_range) {
				errors |= range_err;
			}
			prev_chan = chan;
		}
		if (errors != 0) {
			err++;
			if ((errors & seq_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ao_cmdtest: "
					"channel numbers must increase\n",
					dev->minor);
			}
			if ((errors & range_err) != 0) {
				DPRINTK("comedi%d: amplc_pci230: ao_cmdtest: "
					"channels must have the same range\n",
					dev->minor);
			}
		}
	}

	if (err)
		return 5;

	return 0;
}