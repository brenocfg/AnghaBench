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
struct comedi_cmd {scalar_t__ start_src; scalar_t__ scan_begin_src; scalar_t__ convert_src; scalar_t__ stop_src; unsigned long chanlist_len; unsigned long stop_arg; scalar_t__ scan_end_src; unsigned long scan_end_arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  sample_counter_reg; } ;
struct TYPE_4__ {TYPE_1__ ai_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 unsigned long ME4000_AI_CTRL_BIT_CHANNEL_FIFO ; 
 unsigned long ME4000_AI_CTRL_BIT_DATA_FIFO ; 
 unsigned long ME4000_AI_CTRL_BIT_HF_IRQ ; 
 unsigned long ME4000_AI_CTRL_BIT_MODE_0 ; 
 unsigned long ME4000_AI_CTRL_BIT_MODE_1 ; 
 unsigned long ME4000_AI_CTRL_BIT_MODE_2 ; 
 unsigned long ME4000_AI_CTRL_BIT_SC_IRQ ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_NONE ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  ai_write_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  ai_write_timer (struct comedi_device*,unsigned int,unsigned int,unsigned int) ; 
 TYPE_2__* info ; 
 int /*<<< orphan*/  me4000_outl (struct comedi_device*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ai_prepare(struct comedi_device *dev,
		      struct comedi_subdevice *s,
		      struct comedi_cmd *cmd,
		      unsigned int init_ticks,
		      unsigned int scan_ticks, unsigned int chan_ticks)
{

	unsigned long tmp = 0;

	CALL_PDEBUG("In ai_prepare()\n");

	/* Write timer arguments */
	ai_write_timer(dev, init_ticks, scan_ticks, chan_ticks);

	/* Reset control register */
	me4000_outl(dev, tmp, info->ai_context.ctrl_reg);

	/* Start sources */
	if ((cmd->start_src == TRIG_EXT &&
	     cmd->scan_begin_src == TRIG_TIMER &&
	     cmd->convert_src == TRIG_TIMER) ||
	    (cmd->start_src == TRIG_EXT &&
	     cmd->scan_begin_src == TRIG_FOLLOW &&
	     cmd->convert_src == TRIG_TIMER)) {
		tmp = ME4000_AI_CTRL_BIT_MODE_1 |
		    ME4000_AI_CTRL_BIT_CHANNEL_FIFO |
		    ME4000_AI_CTRL_BIT_DATA_FIFO;
	} else if (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_EXT &&
		   cmd->convert_src == TRIG_TIMER) {
		tmp = ME4000_AI_CTRL_BIT_MODE_2 |
		    ME4000_AI_CTRL_BIT_CHANNEL_FIFO |
		    ME4000_AI_CTRL_BIT_DATA_FIFO;
	} else if (cmd->start_src == TRIG_EXT &&
		   cmd->scan_begin_src == TRIG_EXT &&
		   cmd->convert_src == TRIG_EXT) {
		tmp = ME4000_AI_CTRL_BIT_MODE_0 |
		    ME4000_AI_CTRL_BIT_MODE_1 |
		    ME4000_AI_CTRL_BIT_CHANNEL_FIFO |
		    ME4000_AI_CTRL_BIT_DATA_FIFO;
	} else {
		tmp = ME4000_AI_CTRL_BIT_MODE_0 |
		    ME4000_AI_CTRL_BIT_CHANNEL_FIFO |
		    ME4000_AI_CTRL_BIT_DATA_FIFO;
	}

	/* Stop triggers */
	if (cmd->stop_src == TRIG_COUNT) {
		me4000_outl(dev, cmd->chanlist_len * cmd->stop_arg,
			    info->ai_context.sample_counter_reg);
		tmp |= ME4000_AI_CTRL_BIT_HF_IRQ | ME4000_AI_CTRL_BIT_SC_IRQ;
	} else if (cmd->stop_src == TRIG_NONE &&
		   cmd->scan_end_src == TRIG_COUNT) {
		me4000_outl(dev, cmd->scan_end_arg,
			    info->ai_context.sample_counter_reg);
		tmp |= ME4000_AI_CTRL_BIT_HF_IRQ | ME4000_AI_CTRL_BIT_SC_IRQ;
	} else {
		tmp |= ME4000_AI_CTRL_BIT_HF_IRQ;
	}

	/* Write the setup to the control register */
	me4000_outl(dev, tmp, info->ai_context.ctrl_reg);

	/* Write the channel list */
	ai_write_chanlist(dev, s, cmd);

	return 0;
}