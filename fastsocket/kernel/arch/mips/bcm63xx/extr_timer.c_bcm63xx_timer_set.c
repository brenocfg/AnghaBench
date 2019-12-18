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
 int BCM63XX_TIMER_COUNT ; 
 int EINVAL ; 
 int TIMER_CTL_COUNTDOWN_MASK ; 
 int TIMER_CTL_MONOTONIC_MASK ; 
 int /*<<< orphan*/  TIMER_CTLx_REG (int) ; 
 int bcm63xx_timer_countdown (unsigned int) ; 
 int bcm_timer_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_timer_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_reg_lock ; 

int bcm63xx_timer_set(int id, int monotonic, unsigned int countdown_us)
{
	u32 reg, countdown;
	unsigned long flags;

	if (id >= BCM63XX_TIMER_COUNT)
		return -EINVAL;

	countdown = bcm63xx_timer_countdown(countdown_us);
	if (countdown & ~TIMER_CTL_COUNTDOWN_MASK)
		return -EINVAL;

	spin_lock_irqsave(&timer_reg_lock, flags);
	reg = bcm_timer_readl(TIMER_CTLx_REG(id));

	if (monotonic)
		reg &= ~TIMER_CTL_MONOTONIC_MASK;
	else
		reg |= TIMER_CTL_MONOTONIC_MASK;

	reg &= ~TIMER_CTL_COUNTDOWN_MASK;
	reg |= countdown;
	bcm_timer_writel(reg, TIMER_CTLx_REG(id));

	spin_unlock_irqrestore(&timer_reg_lock, flags);
	return 0;
}