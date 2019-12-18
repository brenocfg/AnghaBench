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
struct hw_fifo_info {unsigned int num_segments; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {struct hw_fifo_info* ai_fifo; } ;

/* Variables and functions */
 unsigned int ai_fifo_size (struct comedi_device*) ; 
 TYPE_1__* board (struct comedi_device*) ; 
 unsigned int bytes_in_sample ; 
 int set_ai_fifo_size (struct comedi_device*,int) ; 

__attribute__((used)) static int ai_config_block_size(struct comedi_device *dev, unsigned int *data)
{
	int fifo_size;
	const struct hw_fifo_info *const fifo = board(dev)->ai_fifo;
	unsigned int block_size, requested_block_size;
	int retval;

	requested_block_size = data[1];

	if (requested_block_size) {
		fifo_size =
		    requested_block_size * fifo->num_segments / bytes_in_sample;

		retval = set_ai_fifo_size(dev, fifo_size);
		if (retval < 0)
			return retval;

	}

	block_size = ai_fifo_size(dev) / fifo->num_segments * bytes_in_sample;

	data[1] = block_size;

	return 2;
}