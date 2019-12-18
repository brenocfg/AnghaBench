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
struct comedi_cmd {scalar_t__ convert_src; int convert_arg; } ;

/* Variables and functions */
 scalar_t__ TRIG_TIMER ; 
 unsigned int dma_buffer_size ; 
 unsigned int sample_size ; 

__attribute__((used)) static unsigned int labpc_suggest_transfer_size(struct comedi_cmd cmd)
{
	unsigned int size;
	unsigned int freq;

	if (cmd.convert_src == TRIG_TIMER)
		freq = 1000000000 / cmd.convert_arg;
	/*  return some default value */
	else
		freq = 0xffffffff;

	/*  make buffer fill in no more than 1/3 second */
	size = (freq / 3) * sample_size;

	/*  set a minimum and maximum size allowed */
	if (size > dma_buffer_size)
		size = dma_buffer_size - dma_buffer_size % sample_size;
	else if (size < sample_size)
		size = sample_size;

	return size;
}