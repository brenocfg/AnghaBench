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
struct at_dma {int all_chan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSR ; 
 int /*<<< orphan*/  EBCIDR ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dma_readl (struct at_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writel (struct at_dma*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void at_dma_off(struct at_dma *atdma)
{
	dma_writel(atdma, EN, 0);

	/* disable all interrupts */
	dma_writel(atdma, EBCIDR, -1L);

	/* confirm that all channels are disabled */
	while (dma_readl(atdma, CHSR) & atdma->all_chan_mask)
		cpu_relax();
}