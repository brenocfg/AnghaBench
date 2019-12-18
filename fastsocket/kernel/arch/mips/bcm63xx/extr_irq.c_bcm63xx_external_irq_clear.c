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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXTIRQ_CFG_CLEAR (unsigned int) ; 
 scalar_t__ IRQ_EXT_BASE ; 
 int /*<<< orphan*/  PERF_EXTIRQ_CFG_REG ; 
 int /*<<< orphan*/  bcm_perf_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_perf_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm63xx_external_irq_clear(unsigned int irq)
{
	u32 reg;

	irq -= IRQ_EXT_BASE;
	reg = bcm_perf_readl(PERF_EXTIRQ_CFG_REG);
	reg |= EXTIRQ_CFG_CLEAR(irq);
	bcm_perf_writel(reg, PERF_EXTIRQ_CFG_REG);
}