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
 int /*<<< orphan*/  INTMR1 ; 
 int clps_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int1_mask(unsigned int irq)
{
	u32 intmr1;

	intmr1 = clps_readl(INTMR1);
	intmr1 &= ~(1 << irq);
	clps_writel(intmr1, INTMR1);
}