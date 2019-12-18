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
 int /*<<< orphan*/  INTMR2 ; 
 int clps_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int2_unmask(unsigned int irq)
{
	u32 intmr2;

	intmr2 = clps_readl(INTMR2);
	intmr2 |= 1 << (irq - 16);
	clps_writel(intmr2, INTMR2);
}