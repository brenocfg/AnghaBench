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
struct comedi_device {int dummy; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; scalar_t__ start_arg; unsigned int convert_arg; int chanlist_len; int scan_end_arg; int stop_arg; int flags; int scan_begin_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  divisor2; int /*<<< orphan*/  divisor1; } ;
struct TYPE_3__ {unsigned int ai_speed; } ;

/* Variables and functions */
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_BASE ; 
#define  TRIG_COUNT 129 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
#define  TRIG_NONE 128 
 int TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 int TRIG_TIMER ; 
 int UNIPOLAR ; 
 unsigned int burst_convert_arg (unsigned int,int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int das1800_ai_do_cmdtest(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_cmd *cmd)
{
	int err = 0;
	int tmp;
	unsigned int tmp_arg;
	int i;
	int unipolar;

	/* step 1: make sure trigger sources are trivially valid */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW | TRIG_EXT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	cmd->scan_begin_src &= TRIG_FOLLOW | TRIG_TIMER | TRIG_EXT;
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;

	tmp = cmd->convert_src;
	cmd->convert_src &= TRIG_TIMER | TRIG_EXT;
	if (!cmd->convert_src || tmp != cmd->convert_src)
		err++;

	tmp = cmd->scan_end_src;
	cmd->scan_end_src &= TRIG_COUNT;
	if (!cmd->scan_end_src || tmp != cmd->scan_end_src)
		err++;

	tmp = cmd->stop_src;
	cmd->stop_src &= TRIG_COUNT | TRIG_EXT | TRIG_NONE;
	if (!cmd->stop_src || tmp != cmd->stop_src)
		err++;

	if (err)
		return 1;

	/* step 2: make sure trigger sources are unique and mutually compatible */

	/*  uniqueness check */
	if (cmd->start_src != TRIG_NOW && cmd->start_src != TRIG_EXT)
		err++;
	if (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->scan_begin_src != TRIG_TIMER &&
	    cmd->scan_begin_src != TRIG_EXT)
		err++;
	if (cmd->convert_src != TRIG_TIMER && cmd->convert_src != TRIG_EXT)
		err++;
	if (cmd->stop_src != TRIG_COUNT &&
	    cmd->stop_src != TRIG_NONE && cmd->stop_src != TRIG_EXT)
		err++;
	/* compatibility check */
	if (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->convert_src != TRIG_TIMER)
		err++;

	if (err)
		return 2;

	/* step 3: make sure arguments are trivially compatible */

	if (cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}
	if (cmd->convert_src == TRIG_TIMER) {
		if (cmd->convert_arg < thisboard->ai_speed) {
			cmd->convert_arg = thisboard->ai_speed;
			err++;
		}
	}
	if (!cmd->chanlist_len) {
		cmd->chanlist_len = 1;
		err++;
	}
	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}

	switch (cmd->stop_src) {
	case TRIG_COUNT:
		if (!cmd->stop_arg) {
			cmd->stop_arg = 1;
			err++;
		}
		break;
	case TRIG_NONE:
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
		break;
	default:
		break;
	}

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		/*  if we are not in burst mode */
		if (cmd->scan_begin_src == TRIG_FOLLOW) {
			tmp_arg = cmd->convert_arg;
			/* calculate counter values that give desired timing */
			i8253_cascade_ns_to_timer_2div(TIMER_BASE,
						       &(devpriv->divisor1),
						       &(devpriv->divisor2),
						       &(cmd->convert_arg),
						       cmd->
						       flags & TRIG_ROUND_MASK);
			if (tmp_arg != cmd->convert_arg)
				err++;
		}
		/*  if we are in burst mode */
		else {
			/*  check that convert_arg is compatible */
			tmp_arg = cmd->convert_arg;
			cmd->convert_arg =
			    burst_convert_arg(cmd->convert_arg,
					      cmd->flags & TRIG_ROUND_MASK);
			if (tmp_arg != cmd->convert_arg)
				err++;

			if (cmd->scan_begin_src == TRIG_TIMER) {
				/*  if scans are timed faster than conversion rate allows */
				if (cmd->convert_arg * cmd->chanlist_len >
				    cmd->scan_begin_arg) {
					cmd->scan_begin_arg =
					    cmd->convert_arg *
					    cmd->chanlist_len;
					err++;
				}
				tmp_arg = cmd->scan_begin_arg;
				/* calculate counter values that give desired timing */
				i8253_cascade_ns_to_timer_2div(TIMER_BASE,
							       &(devpriv->
								 divisor1),
							       &(devpriv->
								 divisor2),
							       &(cmd->
								 scan_begin_arg),
							       cmd->
							       flags &
							       TRIG_ROUND_MASK);
				if (tmp_arg != cmd->scan_begin_arg)
					err++;
			}
		}
	}

	if (err)
		return 4;

	/*  make sure user is not trying to mix unipolar and bipolar ranges */
	if (cmd->chanlist) {
		unipolar = CR_RANGE(cmd->chanlist[0]) & UNIPOLAR;
		for (i = 1; i < cmd->chanlist_len; i++) {
			if (unipolar != (CR_RANGE(cmd->chanlist[i]) & UNIPOLAR)) {
				comedi_error(dev,
					     "unipolar and bipolar ranges cannot be mixed in the chanlist");
				err++;
				break;
			}
		}
	}

	if (err)
		return 5;

	return 0;
}