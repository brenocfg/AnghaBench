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
 int BCM63XX_TIMER_COUNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  TIMER_CTL_ENABLE_MASK ; 
 int /*<<< orphan*/  TIMER_CTLx_REG (int) ; 
 int /*<<< orphan*/  TIMER_IRQSTAT_REG ; 
 int /*<<< orphan*/  TIMER_IRQSTAT_TIMER_IR_EN (int) ; 
 int /*<<< orphan*/  bcm_timer_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_timer_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_reg_lock ; 

int bcm63xx_timer_enable(int id)
{
	u32 reg;
	unsigned long flags;

	if (id >= BCM63XX_TIMER_COUNT)
		return -EINVAL;

	spin_lock_irqsave(&timer_reg_lock, flags);

	reg = bcm_timer_readl(TIMER_CTLx_REG(id));
	reg |= TIMER_CTL_ENABLE_MASK;
	bcm_timer_writel(reg, TIMER_CTLx_REG(id));

	reg = bcm_timer_readl(TIMER_IRQSTAT_REG);
	reg |= TIMER_IRQSTAT_TIMER_IR_EN(id);
	bcm_timer_writel(reg, TIMER_IRQSTAT_REG);

	spin_unlock_irqrestore(&timer_reg_lock, flags);
	return 0;
}