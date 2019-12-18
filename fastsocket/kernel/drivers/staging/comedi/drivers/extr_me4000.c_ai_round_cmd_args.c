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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned int start_arg; unsigned int scan_begin_arg; unsigned int convert_arg; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 int /*<<< orphan*/  PDEBUG (char*,unsigned int) ; 
 int TRIG_ROUND_NEAREST ; 
 int TRIG_ROUND_UP ; 

__attribute__((used)) static int ai_round_cmd_args(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_cmd *cmd,
			     unsigned int *init_ticks,
			     unsigned int *scan_ticks, unsigned int *chan_ticks)
{

	int rest;

	CALL_PDEBUG("In ai_round_cmd_args()\n");

	*init_ticks = 0;
	*scan_ticks = 0;
	*chan_ticks = 0;

	PDEBUG("ai_round_cmd_arg(): start_arg = %d\n", cmd->start_arg);
	PDEBUG("ai_round_cmd_arg(): scan_begin_arg = %d\n",
	       cmd->scan_begin_arg);
	PDEBUG("ai_round_cmd_arg(): convert_arg = %d\n", cmd->convert_arg);

	if (cmd->start_arg) {
		*init_ticks = (cmd->start_arg * 33) / 1000;
		rest = (cmd->start_arg * 33) % 1000;

		if (cmd->flags & TRIG_ROUND_NEAREST) {
			if (rest > 33)
				(*init_ticks)++;
		} else if (cmd->flags & TRIG_ROUND_UP) {
			if (rest)
				(*init_ticks)++;
		}
	}

	if (cmd->scan_begin_arg) {
		*scan_ticks = (cmd->scan_begin_arg * 33) / 1000;
		rest = (cmd->scan_begin_arg * 33) % 1000;

		if (cmd->flags & TRIG_ROUND_NEAREST) {
			if (rest > 33)
				(*scan_ticks)++;
		} else if (cmd->flags & TRIG_ROUND_UP) {
			if (rest)
				(*scan_ticks)++;
		}
	}

	if (cmd->convert_arg) {
		*chan_ticks = (cmd->convert_arg * 33) / 1000;
		rest = (cmd->convert_arg * 33) % 1000;

		if (cmd->flags & TRIG_ROUND_NEAREST) {
			if (rest > 33)
				(*chan_ticks)++;
		} else if (cmd->flags & TRIG_ROUND_UP) {
			if (rest)
				(*chan_ticks)++;
		}
	}

	PDEBUG("ai_round_cmd_args(): init_ticks = %d\n", *init_ticks);
	PDEBUG("ai_round_cmd_args(): scan_ticks = %d\n", *scan_ticks);
	PDEBUG("ai_round_cmd_args(): chan_ticks = %d\n", *chan_ticks);

	return 0;
}