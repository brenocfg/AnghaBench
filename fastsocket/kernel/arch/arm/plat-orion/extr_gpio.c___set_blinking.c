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
 int /*<<< orphan*/  GPIO_BLINK_EN (unsigned int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __set_blinking(unsigned pin, int blink)
{
	u32 u;

	u = readl(GPIO_BLINK_EN(pin));
	if (blink)
		u |= 1 << (pin & 31);
	else
		u &= ~(1 << (pin & 31));
	writel(u, GPIO_BLINK_EN(pin));
}