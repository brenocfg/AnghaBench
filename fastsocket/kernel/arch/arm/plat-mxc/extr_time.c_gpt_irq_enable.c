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
 int MX1_2_TCTL_IRQEN ; 
 scalar_t__ MX3_IR ; 
 scalar_t__ MXC_TCTL ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ cpu_is_mx25 () ; 
 scalar_t__ cpu_is_mx3 () ; 
 scalar_t__ timer_base ; 

__attribute__((used)) static inline void gpt_irq_enable(void)
{
	if (cpu_is_mx3() || cpu_is_mx25())
		__raw_writel(1<<0, timer_base + MX3_IR);
	else {
		__raw_writel(__raw_readl(timer_base + MXC_TCTL) | MX1_2_TCTL_IRQEN,
			timer_base + MXC_TCTL);
	}
}