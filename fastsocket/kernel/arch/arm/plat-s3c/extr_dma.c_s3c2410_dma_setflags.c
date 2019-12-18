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
struct s3c2410_dma_chan {unsigned int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 struct s3c2410_dma_chan* s3c_dma_lookup_channel (unsigned int) ; 

int s3c2410_dma_setflags(unsigned int channel, unsigned int flags)
{
	struct s3c2410_dma_chan *chan = s3c_dma_lookup_channel(channel);

	if (chan == NULL)
		return -EINVAL;

	chan->flags = flags;
	return 0;
}