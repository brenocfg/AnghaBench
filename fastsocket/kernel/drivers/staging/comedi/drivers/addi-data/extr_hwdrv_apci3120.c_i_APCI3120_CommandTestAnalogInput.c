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
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; scalar_t__ start_arg; int scan_begin_arg; int convert_arg; int chanlist_len; int stop_arg; int scan_end_arg; } ;
struct TYPE_2__ {int ui_MinDelaytimeNs; int ui_MinAcquisitiontimeNs; int i_AiChannelList; } ;

/* Variables and functions */
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 TYPE_1__* this_board ; 

int i_APCI3120_CommandTestAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_cmd *cmd)
{
	int err = 0;
	int tmp;		/*  divisor1,divisor2; */

	/*  step 1: make sure trigger sources are trivially valid */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW | TRIG_EXT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;

	tmp = cmd->scan_begin_src;
	cmd->scan_begin_src &= TRIG_TIMER | TRIG_FOLLOW;
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;

	tmp = cmd->convert_src;
	cmd->convert_src &= TRIG_TIMER;
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

	if (cmd->start_src != TRIG_NOW && cmd->start_src != TRIG_EXT) {
		err++;
	}

	if (cmd->scan_begin_src != TRIG_TIMER &&
		cmd->scan_begin_src != TRIG_FOLLOW)
		err++;

	if (cmd->convert_src != TRIG_TIMER)
		err++;

	if (cmd->scan_end_src != TRIG_COUNT) {
		cmd->scan_end_src = TRIG_COUNT;
		err++;
	}

	if (cmd->stop_src != TRIG_NONE && cmd->stop_src != TRIG_COUNT)
		err++;

	if (err)
		return 2;

	/*  step 3: make sure arguments are trivially compatible */

	if (cmd->start_arg != 0) {
		cmd->start_arg = 0;
		err++;
	}

	if (cmd->scan_begin_src == TRIG_TIMER)	/*  Test Delay timing */
	{
		if (cmd->scan_begin_arg < this_board->ui_MinDelaytimeNs) {
			cmd->scan_begin_arg = this_board->ui_MinDelaytimeNs;
			err++;
		}
	}

	if (cmd->convert_src == TRIG_TIMER)	/*  Test Acquisition timing */
	{
		if (cmd->scan_begin_src == TRIG_TIMER) {
			if ((cmd->convert_arg)
				&& (cmd->convert_arg <
					this_board->ui_MinAcquisitiontimeNs)) {
				cmd->convert_arg =
					this_board->ui_MinAcquisitiontimeNs;
				err++;
			}
		} else {
			if (cmd->convert_arg <
				this_board->ui_MinAcquisitiontimeNs) {
				cmd->convert_arg =
					this_board->ui_MinAcquisitiontimeNs;
				err++;

			}
		}
	}

	if (!cmd->chanlist_len) {
		cmd->chanlist_len = 1;
		err++;
	}
	if (cmd->chanlist_len > this_board->i_AiChannelList) {
		cmd->chanlist_len = this_board->i_AiChannelList;
		err++;
	}
	if (cmd->stop_src == TRIG_COUNT) {
		if (!cmd->stop_arg) {
			cmd->stop_arg = 1;
			err++;
		}
	} else {		/*  TRIG_NONE */
		if (cmd->stop_arg != 0) {
			cmd->stop_arg = 0;
			err++;
		}
	}

	if (err)
		return 3;

	/*  step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {

		if (cmd->scan_begin_src == TRIG_TIMER &&
			cmd->scan_begin_arg <
			cmd->convert_arg * cmd->scan_end_arg) {
			cmd->scan_begin_arg =
				cmd->convert_arg * cmd->scan_end_arg;
			err++;
		}
	}

	if (err)
		return 4;

	return 0;
}