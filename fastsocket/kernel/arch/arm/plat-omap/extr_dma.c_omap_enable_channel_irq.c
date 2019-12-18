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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  enabled_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CICR (int) ; 
 int /*<<< orphan*/  CSR (int) ; 
 int /*<<< orphan*/  OMAP2_DMA_CSR_CLEAR_MASK ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 TYPE_1__* dma_chan ; 
 int /*<<< orphan*/  dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void omap_enable_channel_irq(int lch)
{
	u32 status;

	/* Clear CSR */
	if (cpu_class_is_omap1())
		status = dma_read(CSR(lch));
	else if (cpu_class_is_omap2())
		dma_write(OMAP2_DMA_CSR_CLEAR_MASK, CSR(lch));

	/* Enable some nice interrupts. */
	dma_write(dma_chan[lch].enabled_irqs, CICR(lch));
}