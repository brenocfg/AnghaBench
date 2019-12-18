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
 scalar_t__ IRQ_INTERNAL_BASE ; 
 int /*<<< orphan*/  PERF_IRQMASK_REG ; 
 int bcm_perf_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_perf_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm63xx_internal_irq_mask(unsigned int irq)
{
	u32 mask;

	irq -= IRQ_INTERNAL_BASE;
	mask = bcm_perf_readl(PERF_IRQMASK_REG);
	mask &= ~(1 << irq);
	bcm_perf_writel(mask, PERF_IRQMASK_REG);
}