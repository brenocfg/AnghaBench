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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int setup_dma_descriptors (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int dio_config_block_size(struct comedi_device *dev, unsigned int *data)
{
	unsigned int requested_block_size;
	int retval;

	requested_block_size = data[1];

	retval = setup_dma_descriptors(dev, requested_block_size);
	if (retval < 0)
		return retval;

	data[1] = retval;

	return 2;
}