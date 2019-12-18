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
typedef  int u32 ;
typedef  int /*<<< orphan*/  dma_chan_link_map ;
struct TYPE_2__ {int next_lch; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR (int) ; 
 int /*<<< orphan*/  CLNK_CTRL (int) ; 
 scalar_t__ OMAP2430_REV_ES1_0 ; 
 int OMAP_DMA4_LOGICAL_DMA_CH_COUNT ; 
 int /*<<< orphan*/  OMAP_DMA_ACTIVE ; 
 int OMAP_DMA_CCR_EN ; 
 scalar_t__ cpu_is_omap242x () ; 
 scalar_t__ cpu_is_omap243x () ; 
 scalar_t__ cpu_is_omap24xx () ; 
 TYPE_1__* dma_chan ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_lnk (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap_dma_in_1510_mode () ; 
 int /*<<< orphan*/  omap_enable_channel_irq (int) ; 
 scalar_t__ omap_type () ; 

void omap_start_dma(int lch)
{
	u32 l;

	if (!omap_dma_in_1510_mode() && dma_chan[lch].next_lch != -1) {
		int next_lch, cur_lch;
		char dma_chan_link_map[OMAP_DMA4_LOGICAL_DMA_CH_COUNT];

		dma_chan_link_map[lch] = 1;
		/* Set the link register of the first channel */
		enable_lnk(lch);

		memset(dma_chan_link_map, 0, sizeof(dma_chan_link_map));
		cur_lch = dma_chan[lch].next_lch;
		do {
			next_lch = dma_chan[cur_lch].next_lch;

			/* The loop case: we've been here already */
			if (dma_chan_link_map[cur_lch])
				break;
			/* Mark the current channel */
			dma_chan_link_map[cur_lch] = 1;

			enable_lnk(cur_lch);
			omap_enable_channel_irq(cur_lch);

			cur_lch = next_lch;
		} while (next_lch != -1);
	} else if (cpu_is_omap242x() ||
		(cpu_is_omap243x() &&  omap_type() <= OMAP2430_REV_ES1_0)) {

		/* Errata: Need to write lch even if not using chaining */
		dma_write(lch, CLNK_CTRL(lch));
	}

	omap_enable_channel_irq(lch);

	l = dma_read(CCR(lch));

	/*
	 * Errata: On ES2.0 BUFFERING disable must be set.
	 * This will always fail on ES1.0
	 */
	if (cpu_is_omap24xx())
		l |= OMAP_DMA_CCR_EN;

	l |= OMAP_DMA_CCR_EN;
	dma_write(l, CCR(lch));

	dma_chan[lch].flags |= OMAP_DMA_ACTIVE;
}