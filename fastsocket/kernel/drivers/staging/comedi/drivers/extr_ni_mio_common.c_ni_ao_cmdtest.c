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
struct comedi_cmd {int flags; int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; unsigned int start_arg; int scan_begin_arg; scalar_t__ convert_arg; scalar_t__ scan_end_arg; scalar_t__ chanlist_len; int stop_arg; } ;
struct TYPE_4__ {int ao_speed; } ;
struct TYPE_3__ {int clock_ns; } ;

/* Variables and functions */
 int CMDF_WRITE ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_EDGE ; 
 unsigned int CR_INVERT ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_INT ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 int TRIG_TIMER ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  ni_ns_to_timer (struct comedi_device*,int,int) ; 
 int ni_timer_to_ns (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_cmdtest(struct comedi_device *dev, struct comedi_subdevice *s,
			 struct comedi_cmd *cmd)
{
	int err = 0;
	int tmp;

	/* step 1: make sure trigger sources are trivially valid */

	if ((cmd->flags & CMDF_WRITE) == 0) {
		cmd->flags |= CMDF_WRITE;
	}

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_INT | TRIG_EXT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	cmd->scan_begin_src &= TRIG_TIMER | TRIG_EXT;
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

	/* step 2: make sure trigger sources are unique and mutually compatible */

	if (cmd->stop_src != TRIG_COUNT && cmd->stop_src != TRIG_NONE)
		err++;

	if (err)
		return 2;

	/* step 3: make sure arguments are trivially compatible */

	if (cmd->start_src == TRIG_EXT) {
		/* external trigger */
		unsigned int tmp = CR_CHAN(cmd->start_arg);

		if (tmp > 18)
			tmp = 18;
		tmp |= (cmd->start_arg & (CR_INVERT | CR_EDGE));
		if (cmd->start_arg != tmp) {
			cmd->start_arg = tmp;
			err++;
		}
	} else {
		if (cmd->start_arg != 0) {
			/* true for both TRIG_NOW and TRIG_INT */
			cmd->start_arg = 0;
			err++;
		}
	}
	if (cmd->scan_begin_src == TRIG_TIMER) {
		if (cmd->scan_begin_arg < boardtype.ao_speed) {
			cmd->scan_begin_arg = boardtype.ao_speed;
			err++;
		}
		if (cmd->scan_begin_arg > devpriv->clock_ns * 0xffffff) {	/* XXX check */
			cmd->scan_begin_arg = devpriv->clock_ns * 0xffffff;
			err++;
		}
	}
	if (cmd->convert_arg != 0) {
		cmd->convert_arg = 0;
		err++;
	}
	if (cmd->scan_end_arg != cmd->chanlist_len) {
		cmd->scan_end_arg = cmd->chanlist_len;
		err++;
	}
	if (cmd->stop_src == TRIG_COUNT) {	/* XXX check */
		if (cmd->stop_arg > 0x00ffffff) {
			cmd->stop_arg = 0x00ffffff;
			err++;
		}
	} else {
		/* TRIG_NONE */
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
	}

	if (err)
		return 3;

	/* step 4: fix up any arguments */
	if (cmd->scan_begin_src == TRIG_TIMER) {
		tmp = cmd->scan_begin_arg;
		cmd->scan_begin_arg =
		    ni_timer_to_ns(dev, ni_ns_to_timer(dev,
						       cmd->scan_begin_arg,
						       cmd->
						       flags &
						       TRIG_ROUND_MASK));
		if (tmp != cmd->scan_begin_arg)
			err++;
	}
	if (err)
		return 4;

	/* step 5: fix up chanlist */

	if (err)
		return 5;

	return 0;
}