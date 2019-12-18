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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CICR (int) ; 
 int /*<<< orphan*/  CLNK_CTRL (int) ; 
 int /*<<< orphan*/  OMAP_DMA_ACTIVE ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 TYPE_1__* dma_chan ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_disable_channel_irq (int) ; 

__attribute__((used)) static inline void disable_lnk(int lch)
{
	u32 l;

	l = dma_read(CLNK_CTRL(lch));

	/* Disable interrupts */
	if (cpu_class_is_omap1()) {
		dma_write(0, CICR(lch));
		/* Set the STOP_LNK bit */
		l |= 1 << 14;
	}

	if (cpu_class_is_omap2()) {
		omap_disable_channel_irq(lch);
		/* Clear the ENABLE_LNK bit */
		l &= ~(1 << 15);
	}

	dma_write(l, CLNK_CTRL(lch));
	dma_chan[lch].flags &= ~OMAP_DMA_ACTIVE;
}