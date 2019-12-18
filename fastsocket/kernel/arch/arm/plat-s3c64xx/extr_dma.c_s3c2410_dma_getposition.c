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
struct s3c2410_dma_chan {scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PL080_CH_DST_ADDR ; 
 scalar_t__ PL080_CH_SRC_ADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct s3c2410_dma_chan* s3c_dma_lookup_channel (unsigned int) ; 

int s3c2410_dma_getposition(unsigned int channel,
			    dma_addr_t *src, dma_addr_t *dst)
{
	struct s3c2410_dma_chan *chan = s3c_dma_lookup_channel(channel);

	WARN_ON(!chan);
	if (!chan)
		return -EINVAL;

	if (src != NULL)
		*src = readl(chan->regs + PL080_CH_SRC_ADDR);

	if (dst != NULL)
		*dst = readl(chan->regs + PL080_CH_DST_ADDR);

	return 0;
}