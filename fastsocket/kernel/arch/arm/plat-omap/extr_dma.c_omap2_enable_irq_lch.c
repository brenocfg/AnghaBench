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
 int /*<<< orphan*/  IRQENABLE_L0 ; 
 int /*<<< orphan*/  cpu_class_is_omap2 () ; 
 int /*<<< orphan*/  dma_chan_lock ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void omap2_enable_irq_lch(int lch)
{
	u32 val;
	unsigned long flags;

	if (!cpu_class_is_omap2())
		return;

	spin_lock_irqsave(&dma_chan_lock, flags);
	val = dma_read(IRQENABLE_L0);
	val |= 1 << lch;
	dma_write(val, IRQENABLE_L0);
	spin_unlock_irqrestore(&dma_chan_lock, flags);
}