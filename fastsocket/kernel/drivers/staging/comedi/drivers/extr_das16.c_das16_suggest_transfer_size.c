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
struct comedi_device {int dummy; } ;
struct comedi_cmd {scalar_t__ convert_src; int convert_arg; scalar_t__ scan_begin_src; int scan_begin_arg; int chanlist_len; int flags; scalar_t__ stop_src; } ;
struct TYPE_2__ {unsigned int adc_byte_count; scalar_t__ timer_mode; } ;

/* Variables and functions */
 unsigned int DAS16_DMA_SIZE ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_TIMER ; 
 int TRIG_WAKE_EOS ; 
 TYPE_1__* devpriv ; 
 unsigned int sample_size ; 

__attribute__((used)) static unsigned int das16_suggest_transfer_size(struct comedi_device *dev,
						struct comedi_cmd cmd)
{
	unsigned int size;
	unsigned int freq;

	/* if we are using timer interrupt, we don't care how long it
	 * will take to complete transfer since it will be interrupted
	 * by timer interrupt */
	if (devpriv->timer_mode)
		return DAS16_DMA_SIZE;

	/* otherwise, we are relying on dma terminal count interrupt,
	 * so pick a reasonable size */
	if (cmd.convert_src == TRIG_TIMER)
		freq = 1000000000 / cmd.convert_arg;
	else if (cmd.scan_begin_src == TRIG_TIMER)
		freq = (1000000000 / cmd.scan_begin_arg) * cmd.chanlist_len;
	/*  return some default value */
	else
		freq = 0xffffffff;

	if (cmd.flags & TRIG_WAKE_EOS) {
		size = sample_size * cmd.chanlist_len;
	} else {
		/*  make buffer fill in no more than 1/3 second */
		size = (freq / 3) * sample_size;
	}

	/*  set a minimum and maximum size allowed */
	if (size > DAS16_DMA_SIZE)
		size = DAS16_DMA_SIZE - DAS16_DMA_SIZE % sample_size;
	else if (size < sample_size)
		size = sample_size;

	if (cmd.stop_src == TRIG_COUNT && size > devpriv->adc_byte_count)
		size = devpriv->adc_byte_count;

	return size;
}