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

/* Variables and functions */
 unsigned int AU1000_GPIO_0 ; 
 unsigned int AU1000_GPIO_7 ; 
 unsigned int AU1000_INTC1_INT_BASE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SYS_WAKEMSK ; 
 unsigned long au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int au1x_ic1_setwake(unsigned int irq, unsigned int on)
{
	unsigned int bit = irq - AU1000_INTC1_INT_BASE;
	unsigned long wakemsk, flags;

	/* only GPIO 0-7 can act as wakeup source: */
	if ((irq < AU1000_GPIO_0) || (irq > AU1000_GPIO_7))
		return -EINVAL;

	local_irq_save(flags);
	wakemsk = au_readl(SYS_WAKEMSK);
	if (on)
		wakemsk |= 1 << bit;
	else
		wakemsk &= ~(1 << bit);
	au_writel(wakemsk, SYS_WAKEMSK);
	au_sync();
	local_irq_restore(flags);

	return 0;
}