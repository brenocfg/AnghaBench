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
struct comedi_device {int dummy; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; int start_arg; int chanlist_len; int scan_end_arg; int convert_arg; int scan_begin_arg; int stop_arg; } ;
struct TYPE_2__ {scalar_t__ register_layout; int ai_speed; } ;

/* Variables and functions */
#define  TRIG_COUNT 129 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
#define  TRIG_NONE 128 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 scalar_t__ labpc_1200_layout ; 
 int /*<<< orphan*/  labpc_adc_timing (struct comedi_device*,struct comedi_cmd*) ; 
 scalar_t__ labpc_ai_chanlist_invalid (struct comedi_device*,struct comedi_cmd*) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int labpc_ai_cmdtest(struct comedi_device *dev,
			    struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int err = 0;
	int tmp, tmp2;
	int stop_mask;

	/* step 1: make sure trigger sources are trivially valid */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW | TRIG_EXT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	cmd->scan_begin_src &= TRIG_TIMER | TRIG_FOLLOW | TRIG_EXT;
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
	stop_mask = TRIG_COUNT | TRIG_NONE;
	if (thisboard->register_layout == labpc_1200_layout)
		stop_mask |= TRIG_EXT;
	cmd->stop_src &= stop_mask;
	if (!cmd->stop_src || tmp != cmd->stop_src)
		err++;

	if (err)
		return 1;

	/* step 2: make sure trigger sources are unique and mutually compatible */

	if (cmd->start_src != TRIG_NOW && cmd->start_src != TRIG_EXT)
		err++;
	if (cmd->scan_begin_src != TRIG_TIMER &&
	    cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->scan_begin_src != TRIG_EXT)
		err++;
	if (cmd->convert_src != TRIG_TIMER && cmd->convert_src != TRIG_EXT)
		err++;
	if (cmd->stop_src != TRIG_COUNT &&
	    cmd->stop_src != TRIG_EXT && cmd->stop_src != TRIG_NONE)
		err++;

	/*  can't have external stop and start triggers at once */
	if (cmd->start_src == TRIG_EXT && cmd->stop_src == TRIG_EXT)
		err++;

	if (err)
		return 2;

	/* step 3: make sure arguments are trivially compatible */

	if (cmd->start_arg == TRIG_NOW && cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}

	if (!cmd->chanlist_len) {
		err++;
	}
	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}

	if (cmd->convert_src == TRIG_TIMER) {
		if (cmd->convert_arg < thisboard->ai_speed) {
			cmd->convert_arg = thisboard->ai_speed;
			err++;
		}
	}
	/*  make sure scan timing is not too fast */
	if (cmd->scan_begin_src == TRIG_TIMER) {
		if (cmd->convert_src == TRIG_TIMER &&
		    cmd->scan_begin_arg <
		    cmd->convert_arg * cmd->chanlist_len) {
			cmd->scan_begin_arg =
			    cmd->convert_arg * cmd->chanlist_len;
			err++;
		}
		if (cmd->scan_begin_arg <
		    thisboard->ai_speed * cmd->chanlist_len) {
			cmd->scan_begin_arg =
			    thisboard->ai_speed * cmd->chanlist_len;
			err++;
		}
	}
	/*  stop source */
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
		/*  TRIG_EXT doesn't care since it doesn't trigger off a numbered channel */
	default:
		break;
	}

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	tmp = cmd->convert_arg;
	tmp2 = cmd->scan_begin_arg;
	labpc_adc_timing(dev, cmd);
	if (tmp != cmd->convert_arg || tmp2 != cmd->scan_begin_arg)
		err++;

	if (err)
		return 4;

	if (labpc_ai_chanlist_invalid(dev, cmd))
		return 5;

	return 0;
}