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
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; scalar_t__ start_arg; scalar_t__ scan_begin_arg; int convert_arg; int chanlist_len; int scan_end_arg; int stop_arg; int flags; } ;
struct TYPE_4__ {scalar_t__ use_ext_trg; } ;
struct TYPE_3__ {int ai_ns_min; int n_aichan; int /*<<< orphan*/  i8254_osc_base; } ;

/* Variables and functions */
 int MAX_CHANLIST_LEN ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 int TRIG_TIMER ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer (int /*<<< orphan*/ ,int*,int*,int*,int) ; 
 int /*<<< orphan*/  pcl812_cmdtest_out (int,struct comedi_cmd*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int pcl812_ai_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int err = 0;
	int tmp, divisor1, divisor2;

#ifdef PCL812_EXTDEBUG
	printk("pcl812 EDBG: BGN: pcl812_ai_cmdtest(...)\n");
	pcl812_cmdtest_out(-1, cmd);
#endif
	/* step 1: make sure trigger sources are trivially valid */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	cmd->scan_begin_src &= TRIG_FOLLOW;
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;

	tmp = cmd->convert_src;
	if (devpriv->use_ext_trg) {
		cmd->convert_src &= TRIG_EXT;
	} else {
		cmd->convert_src &= TRIG_TIMER;
	}
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

	if (err) {
#ifdef PCL812_EXTDEBUG
		pcl812_cmdtest_out(1, cmd);
		printk
		    ("pcl812 EDBG: BGN: pcl812_ai_cmdtest(...) err=%d ret=1\n",
		     err);
#endif
		return 1;
	}

	/* step 2: make sure trigger sources are unique and mutually compatible */

	if (cmd->start_src != TRIG_NOW) {
		cmd->start_src = TRIG_NOW;
		err++;
	}

	if (cmd->scan_begin_src != TRIG_FOLLOW) {
		cmd->scan_begin_src = TRIG_FOLLOW;
		err++;
	}

	if (devpriv->use_ext_trg) {
		if (cmd->convert_src != TRIG_EXT) {
			cmd->convert_src = TRIG_EXT;
			err++;
		}
	} else {
		if (cmd->convert_src != TRIG_TIMER) {
			cmd->convert_src = TRIG_TIMER;
			err++;
		}
	}

	if (cmd->scan_end_src != TRIG_COUNT) {
		cmd->scan_end_src = TRIG_COUNT;
		err++;
	}

	if (cmd->stop_src != TRIG_NONE && cmd->stop_src != TRIG_COUNT)
		err++;

	if (err) {
#ifdef PCL812_EXTDEBUG
		pcl812_cmdtest_out(2, cmd);
		printk
		    ("pcl812 EDBG: BGN: pcl812_ai_cmdtest(...) err=%d ret=2\n",
		     err);
#endif
		return 2;
	}

	/* step 3: make sure arguments are trivially compatible */

	if (cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}

	if (cmd->scan_begin_arg != 0) {
		cmd->scan_begin_arg = 0;
		err++;
	}

	if (cmd->convert_src == TRIG_TIMER) {
		if (cmd->convert_arg < this_board->ai_ns_min) {
			cmd->convert_arg = this_board->ai_ns_min;
			err++;
		}
	} else {		/* TRIG_EXT */
		if (cmd->convert_arg != 0) {
			cmd->convert_arg = 0;
			err++;
		}
	}

	if (!cmd->chanlist_len) {
		cmd->chanlist_len = 1;
		err++;
	}
	if (cmd->chanlist_len > MAX_CHANLIST_LEN) {
		cmd->chanlist_len = this_board->n_aichan;
		err++;
	}
	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}
	if (cmd->stop_src == TRIG_COUNT) {
		if (!cmd->stop_arg) {
			cmd->stop_arg = 1;
			err++;
		}
	} else {		/* TRIG_NONE */
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
	}

	if (err) {
#ifdef PCL812_EXTDEBUG
		pcl812_cmdtest_out(3, cmd);
		printk
		    ("pcl812 EDBG: BGN: pcl812_ai_cmdtest(...) err=%d ret=3\n",
		     err);
#endif
		return 3;
	}

	/* step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		tmp = cmd->convert_arg;
		i8253_cascade_ns_to_timer(this_board->i8254_osc_base, &divisor1,
					  &divisor2, &cmd->convert_arg,
					  cmd->flags & TRIG_ROUND_MASK);
		if (cmd->convert_arg < this_board->ai_ns_min)
			cmd->convert_arg = this_board->ai_ns_min;
		if (tmp != cmd->convert_arg)
			err++;
	}

	if (err) {
#ifdef PCL812_EXTDEBUG
		printk
		    ("pcl812 EDBG: BGN: pcl812_ai_cmdtest(...) err=%d ret=4\n",
		     err);
#endif
		return 4;
	}

	return 0;
}