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
 int /*<<< orphan*/  GPIO_OUT (unsigned int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_level(unsigned pin, int high)
{
	u32 u;

	u = readl(GPIO_OUT(pin));
	if (high)
		u |= 1 << (pin & 31);
	else
		u &= ~(1 << (pin & 31));
	writel(u, GPIO_OUT(pin));
}