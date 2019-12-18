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
struct s3c2410_dma_chan {int dummy; } ;

/* Variables and functions */
 unsigned int DMACH_LOW_LEVEL ; 
 struct s3c2410_dma_chan* s3c2410_chans ; 
 struct s3c2410_dma_chan** s3c_dma_chan_map ; 

struct s3c2410_dma_chan *s3c_dma_lookup_channel(unsigned int channel)
{
	if (channel & DMACH_LOW_LEVEL)
		return &s3c2410_chans[channel & ~DMACH_LOW_LEVEL];
	else
		return s3c_dma_chan_map[channel];
}