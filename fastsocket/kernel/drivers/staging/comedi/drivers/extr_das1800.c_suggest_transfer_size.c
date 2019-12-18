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
struct comedi_cmd {int scan_begin_src; int convert_src; unsigned int convert_arg; unsigned int scan_begin_arg; unsigned int chanlist_len; scalar_t__ stop_src; int const stop_arg; } ;

/* Variables and functions */
 unsigned int DMA_BUF_SIZE ; 
 scalar_t__ TRIG_COUNT ; 
#define  TRIG_FOLLOW 129 
#define  TRIG_TIMER 128 

__attribute__((used)) static unsigned int suggest_transfer_size(struct comedi_cmd *cmd)
{
	unsigned int size = DMA_BUF_SIZE;
	static const int sample_size = 2;	/*  size in bytes of one sample from board */
	unsigned int fill_time = 300000000;	/*  target time in nanoseconds for filling dma buffer */
	unsigned int max_size;	/*  maximum size we will allow for a transfer */

	/*  make dma buffer fill in 0.3 seconds for timed modes */
	switch (cmd->scan_begin_src) {
	case TRIG_FOLLOW:	/*  not in burst mode */
		if (cmd->convert_src == TRIG_TIMER)
			size = (fill_time / cmd->convert_arg) * sample_size;
		break;
	case TRIG_TIMER:
		size = (fill_time / (cmd->scan_begin_arg * cmd->chanlist_len)) *
		    sample_size;
		break;
	default:
		size = DMA_BUF_SIZE;
		break;
	}

	/*  set a minimum and maximum size allowed */
	max_size = DMA_BUF_SIZE;
	/*  if we are taking limited number of conversions, limit transfer size to that */
	if (cmd->stop_src == TRIG_COUNT &&
	    cmd->stop_arg * cmd->chanlist_len * sample_size < max_size)
		max_size = cmd->stop_arg * cmd->chanlist_len * sample_size;

	if (size > max_size)
		size = max_size;
	if (size < sample_size)
		size = sample_size;

	return size;
}