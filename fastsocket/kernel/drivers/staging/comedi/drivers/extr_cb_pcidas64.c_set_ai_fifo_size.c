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
struct hw_fifo_info {unsigned int sample_packing_ratio; unsigned int num_segments; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {struct hw_fifo_info* ai_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT (char*,unsigned int) ; 
 TYPE_1__* board (struct comedi_device*) ; 
 int set_ai_fifo_segment_length (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int set_ai_fifo_size(struct comedi_device *dev, unsigned int num_samples)
{
	unsigned int num_fifo_entries;
	int retval;
	const struct hw_fifo_info *const fifo = board(dev)->ai_fifo;

	num_fifo_entries = num_samples / fifo->sample_packing_ratio;

	retval = set_ai_fifo_segment_length(dev,
					    num_fifo_entries /
					    fifo->num_segments);
	if (retval < 0)
		return retval;

	num_samples = retval * fifo->num_segments * fifo->sample_packing_ratio;

	DEBUG_PRINT("set hardware fifo size to %i\n", num_samples);

	return num_samples;
}