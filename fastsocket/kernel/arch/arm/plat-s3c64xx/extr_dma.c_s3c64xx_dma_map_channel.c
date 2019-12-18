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
struct s3c2410_dma_chan {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 unsigned int DMACH_PCM1_TX ; 
 struct s3c2410_dma_chan* s3c2410_chans ; 
 struct s3c2410_dma_chan** s3c_dma_chan_map ; 

__attribute__((used)) static struct s3c2410_dma_chan *s3c64xx_dma_map_channel(unsigned int channel)
{
	struct s3c2410_dma_chan *chan;
	unsigned int start, offs;

	start = 0;

	if (channel >= DMACH_PCM1_TX)
		start = 8;

	for (offs = 0; offs < 8; offs++) {
		chan = &s3c2410_chans[start + offs];
		if (!chan->in_use)
			goto found;
	}

	return NULL;

found:
	s3c_dma_chan_map[channel] = chan;
	return chan;
}