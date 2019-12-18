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
struct TYPE_2__ {int next_lch; int next_linked_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLNK_CTRL (int) ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 TYPE_1__* dma_chan ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void enable_lnk(int lch)
{
	u32 l;

	l = dma_read(CLNK_CTRL(lch));

	if (cpu_class_is_omap1())
		l &= ~(1 << 14);

	/* Set the ENABLE_LNK bits */
	if (dma_chan[lch].next_lch != -1)
		l = dma_chan[lch].next_lch | (1 << 15);

#ifndef CONFIG_ARCH_OMAP1
	if (cpu_class_is_omap2())
		if (dma_chan[lch].next_linked_ch != -1)
			l = dma_chan[lch].next_linked_ch | (1 << 15);
#endif

	dma_write(l, CLNK_CTRL(lch));
}