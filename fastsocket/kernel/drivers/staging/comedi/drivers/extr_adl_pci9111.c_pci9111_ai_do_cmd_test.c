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
struct pci9111_board {int ai_channel_nbr; scalar_t__ ai_acquisition_period_min_ns; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ board_ptr; } ;
struct comedi_cmd {scalar_t__ start_src; scalar_t__ scan_begin_src; scalar_t__ convert_src; scalar_t__ scan_end_src; scalar_t__ stop_src; int chanlist_len; scalar_t__ start_arg; scalar_t__ convert_arg; scalar_t__ scan_begin_arg; int scan_end_arg; int stop_arg; int flags; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer_divisor_2; int /*<<< orphan*/  timer_divisor_1; } ;

/* Variables and functions */
 int CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI9111_8254_CLOCK_PERIOD_NS ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_NONE ; 
 scalar_t__ TRIG_NOW ; 
 int TRIG_ROUND_MASK ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  pci9111_check_trigger_src (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
pci9111_ai_do_cmd_test(struct comedi_device *dev,
		       struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	int tmp;
	int error = 0;
	int range, reference;
	int i;
	struct pci9111_board *board = (struct pci9111_board *)dev->board_ptr;

	/*  Step 1 : check if trigger are trivialy valid */

	pci9111_check_trigger_src(cmd->start_src, TRIG_NOW);
	pci9111_check_trigger_src(cmd->scan_begin_src,
				  TRIG_TIMER | TRIG_FOLLOW | TRIG_EXT);
	pci9111_check_trigger_src(cmd->convert_src, TRIG_TIMER | TRIG_EXT);
	pci9111_check_trigger_src(cmd->scan_end_src, TRIG_COUNT);
	pci9111_check_trigger_src(cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (error)
		return 1;

	/*  step 2 : make sure trigger sources are unique and mutually compatible */

	if (cmd->start_src != TRIG_NOW)
		error++;

	if ((cmd->scan_begin_src != TRIG_TIMER) &&
	    (cmd->scan_begin_src != TRIG_FOLLOW) &&
	    (cmd->scan_begin_src != TRIG_EXT))
		error++;

	if ((cmd->convert_src != TRIG_TIMER) && (cmd->convert_src != TRIG_EXT)) {
		error++;
	}
	if ((cmd->convert_src == TRIG_TIMER) &&
	    !((cmd->scan_begin_src == TRIG_TIMER) ||
	      (cmd->scan_begin_src == TRIG_FOLLOW))) {
		error++;
	}
	if ((cmd->convert_src == TRIG_EXT) &&
	    !((cmd->scan_begin_src == TRIG_EXT) ||
	      (cmd->scan_begin_src == TRIG_FOLLOW))) {
		error++;
	}

	if (cmd->scan_end_src != TRIG_COUNT)
		error++;
	if ((cmd->stop_src != TRIG_COUNT) && (cmd->stop_src != TRIG_NONE))
		error++;

	if (error)
		return 2;

	/*  Step 3 : make sure arguments are trivialy compatible */

	if (cmd->chanlist_len < 1) {
		cmd->chanlist_len = 1;
		error++;
	}

	if (cmd->chanlist_len > board->ai_channel_nbr) {
		cmd->chanlist_len = board->ai_channel_nbr;
		error++;
	}

	if ((cmd->start_src == TRIG_NOW) && (cmd->start_arg != 0)) {
		cmd->start_arg = 0;
		error++;
	}

	if ((cmd->convert_src == TRIG_TIMER) &&
	    (cmd->convert_arg < board->ai_acquisition_period_min_ns)) {
		cmd->convert_arg = board->ai_acquisition_period_min_ns;
		error++;
	}
	if ((cmd->convert_src == TRIG_EXT) && (cmd->convert_arg != 0)) {
		cmd->convert_arg = 0;
		error++;
	}

	if ((cmd->scan_begin_src == TRIG_TIMER) &&
	    (cmd->scan_begin_arg < board->ai_acquisition_period_min_ns)) {
		cmd->scan_begin_arg = board->ai_acquisition_period_min_ns;
		error++;
	}
	if ((cmd->scan_begin_src == TRIG_FOLLOW) && (cmd->scan_begin_arg != 0)) {
		cmd->scan_begin_arg = 0;
		error++;
	}
	if ((cmd->scan_begin_src == TRIG_EXT) && (cmd->scan_begin_arg != 0)) {
		cmd->scan_begin_arg = 0;
		error++;
	}

	if ((cmd->scan_end_src == TRIG_COUNT) &&
	    (cmd->scan_end_arg != cmd->chanlist_len)) {
		cmd->scan_end_arg = cmd->chanlist_len;
		error++;
	}

	if ((cmd->stop_src == TRIG_COUNT) && (cmd->stop_arg < 1)) {
		cmd->stop_arg = 1;
		error++;
	}
	if ((cmd->stop_src == TRIG_NONE) && (cmd->stop_arg != 0)) {
		cmd->stop_arg = 0;
		error++;
	}

	if (error)
		return 3;

	/*  Step 4 : fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		tmp = cmd->convert_arg;
		i8253_cascade_ns_to_timer_2div(PCI9111_8254_CLOCK_PERIOD_NS,
					       &(dev_private->timer_divisor_1),
					       &(dev_private->timer_divisor_2),
					       &(cmd->convert_arg),
					       cmd->flags & TRIG_ROUND_MASK);
		if (tmp != cmd->convert_arg)
			error++;
	}
	/*  There's only one timer on this card, so the scan_begin timer must */
	/*  be a multiple of chanlist_len*convert_arg */

	if (cmd->scan_begin_src == TRIG_TIMER) {

		unsigned int scan_begin_min;
		unsigned int scan_begin_arg;
		unsigned int scan_factor;

		scan_begin_min = cmd->chanlist_len * cmd->convert_arg;

		if (cmd->scan_begin_arg != scan_begin_min) {
			if (scan_begin_min < cmd->scan_begin_arg) {
				scan_factor =
				    cmd->scan_begin_arg / scan_begin_min;
				scan_begin_arg = scan_factor * scan_begin_min;
				if (cmd->scan_begin_arg != scan_begin_arg) {
					cmd->scan_begin_arg = scan_begin_arg;
					error++;
				}
			} else {
				cmd->scan_begin_arg = scan_begin_min;
				error++;
			}
		}
	}

	if (error)
		return 4;

	/*  Step 5 : check channel list */

	if (cmd->chanlist) {

		range = CR_RANGE(cmd->chanlist[0]);
		reference = CR_AREF(cmd->chanlist[0]);

		if (cmd->chanlist_len > 1) {
			for (i = 0; i < cmd->chanlist_len; i++) {
				if (CR_CHAN(cmd->chanlist[i]) != i) {
					comedi_error(dev,
						     "entries in chanlist must be consecutive "
						     "channels,counting upwards from 0\n");
					error++;
				}
				if (CR_RANGE(cmd->chanlist[i]) != range) {
					comedi_error(dev,
						     "entries in chanlist must all have the same gain\n");
					error++;
				}
				if (CR_AREF(cmd->chanlist[i]) != reference) {
					comedi_error(dev,
						     "entries in chanlist must all have the same reference\n");
					error++;
				}
			}
		} else {
			if ((CR_CHAN(cmd->chanlist[0]) >
			     (board->ai_channel_nbr - 1))
			    || (CR_CHAN(cmd->chanlist[0]) < 0)) {
				comedi_error(dev,
					     "channel number is out of limits\n");
				error++;
			}
		}
	}

	if (error)
		return 5;

	return 0;

}