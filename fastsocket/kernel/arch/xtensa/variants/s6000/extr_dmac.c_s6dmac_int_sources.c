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
typedef  int u32 ;

/* Variables and functions */
 int S6_DMA_INT0_OVER ; 
 int S6_DMA_INT0_UNDER ; 
 int S6_DMA_INT1_CHANNEL ; 
 int S6_DMA_INT1_MASTER ; 
 int S6_DMA_INT1_MASTER_MASK ; 
 int S6_DMA_INTCLEAR0 ; 
 int S6_DMA_INTCLEAR1 ; 
 int S6_DMA_INTRAW0 ; 
 int S6_DMA_INTRAW1 ; 
 int S6_DMA_LOWWMRKIRQCLR ; 
 int S6_DMA_LOWWMRKIRQSTAT ; 
 int S6_DMA_MASTERERRINFO ; 
 int S6_DMA_MASTERERR_CHAN (int) ; 
 int S6_DMA_MASTERERR_CHAN_MASK ; 
 int S6_DMA_PENDCNTIRQCLR ; 
 int S6_DMA_PENDCNTIRQSTAT ; 
 int S6_DMA_TERMCNTIRQCLR ; 
 int S6_DMA_TERMCNTIRQSTAT ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

u32 s6dmac_int_sources(u32 dmac, u32 channel)
{
	u32 mask, ret, tmp;
	mask = 1 << channel;

	tmp = readl(dmac + S6_DMA_TERMCNTIRQSTAT);
	tmp &= mask;
	writel(tmp, dmac + S6_DMA_TERMCNTIRQCLR);
	ret = tmp >> channel;

	tmp = readl(dmac + S6_DMA_PENDCNTIRQSTAT);
	tmp &= mask;
	writel(tmp, dmac + S6_DMA_PENDCNTIRQCLR);
	ret |= (tmp >> channel) << 1;

	tmp = readl(dmac + S6_DMA_LOWWMRKIRQSTAT);
	tmp &= mask;
	writel(tmp, dmac + S6_DMA_LOWWMRKIRQCLR);
	ret |= (tmp >> channel) << 2;

	tmp = readl(dmac + S6_DMA_INTRAW0);
	tmp &= (mask << S6_DMA_INT0_OVER) | (mask << S6_DMA_INT0_UNDER);
	writel(tmp, dmac + S6_DMA_INTCLEAR0);

	if (tmp & (mask << S6_DMA_INT0_UNDER))
		ret |= 1 << 3;
	if (tmp & (mask << S6_DMA_INT0_OVER))
		ret |= 1 << 4;

	tmp = readl(dmac + S6_DMA_MASTERERRINFO);
	mask <<= S6_DMA_INT1_CHANNEL;
	if (((tmp >> S6_DMA_MASTERERR_CHAN(0)) & S6_DMA_MASTERERR_CHAN_MASK)
			== channel)
		mask |= 1 << S6_DMA_INT1_MASTER;
	if (((tmp >> S6_DMA_MASTERERR_CHAN(1)) & S6_DMA_MASTERERR_CHAN_MASK)
			== channel)
		mask |= 1 << (S6_DMA_INT1_MASTER + 1);
	if (((tmp >> S6_DMA_MASTERERR_CHAN(2)) & S6_DMA_MASTERERR_CHAN_MASK)
			== channel)
		mask |= 1 << (S6_DMA_INT1_MASTER + 2);

	tmp = readl(dmac + S6_DMA_INTRAW1) & mask;
	writel(tmp, dmac + S6_DMA_INTCLEAR1);
	ret |= ((tmp >> channel) & 1) << 5;
	ret |= ((tmp >> S6_DMA_INT1_MASTER) & S6_DMA_INT1_MASTER_MASK) << 6;

	return ret;
}