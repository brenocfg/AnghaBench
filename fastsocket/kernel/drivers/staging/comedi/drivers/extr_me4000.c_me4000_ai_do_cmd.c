#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  start_reg; } ;
struct TYPE_6__ {TYPE_1__ ai_context; } ;
struct TYPE_5__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 int ai_prepare (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*,unsigned int,unsigned int,unsigned int) ; 
 int ai_round_cmd_args (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_3__* info ; 
 int me4000_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  me4000_inl (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int me4000_ai_do_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	int err;
	unsigned int init_ticks = 0;
	unsigned int scan_ticks = 0;
	unsigned int chan_ticks = 0;
	struct comedi_cmd *cmd = &s->async->cmd;

	CALL_PDEBUG("In me4000_ai_do_cmd()\n");

	/* Reset the analog input */
	err = me4000_ai_cancel(dev, s);
	if (err)
		return err;

	/* Round the timer arguments */
	err = ai_round_cmd_args(dev,
				s, cmd, &init_ticks, &scan_ticks, &chan_ticks);
	if (err)
		return err;

	/* Prepare the AI for acquisition */
	err = ai_prepare(dev, s, cmd, init_ticks, scan_ticks, chan_ticks);
	if (err)
		return err;

	/* Start acquistion by dummy read */
	me4000_inl(dev, info->ai_context.start_reg);

	return 0;
}