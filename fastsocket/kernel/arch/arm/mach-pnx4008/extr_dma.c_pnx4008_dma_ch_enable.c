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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_Cx_CONFIG (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VALID_CHANNEL (int) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* dma_channels ; 
 int /*<<< orphan*/  pnx4008_dma_lock () ; 
 int /*<<< orphan*/  pnx4008_dma_unlock () ; 

int pnx4008_dma_ch_enable(int ch)
{
	unsigned long ch_cfg;

	if (!VALID_CHANNEL(ch) || !dma_channels[ch].name)
		return -EINVAL;

	pnx4008_dma_lock();
	ch_cfg = __raw_readl(DMAC_Cx_CONFIG(ch));
	ch_cfg |= 1;
	__raw_writel(ch_cfg, DMAC_Cx_CONFIG(ch));
	pnx4008_dma_unlock();

	return 0;
}