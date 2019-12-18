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
 scalar_t__ MX1_2_TSTAT ; 
 int MX2_TSTAT_CAPT ; 
 int MX2_TSTAT_COMP ; 
 scalar_t__ MX3_TSTAT ; 
 int MX3_TSTAT_OF1 ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ cpu_is_mx1 () ; 
 scalar_t__ cpu_is_mx2 () ; 
 scalar_t__ cpu_is_mx25 () ; 
 scalar_t__ cpu_is_mx3 () ; 
 scalar_t__ timer_base ; 

__attribute__((used)) static void gpt_irq_acknowledge(void)
{
	if (cpu_is_mx1())
		__raw_writel(0, timer_base + MX1_2_TSTAT);
	if (cpu_is_mx2())
		__raw_writel(MX2_TSTAT_CAPT | MX2_TSTAT_COMP, timer_base + MX1_2_TSTAT);
	if (cpu_is_mx3() || cpu_is_mx25())
		__raw_writel(MX3_TSTAT_OF1, timer_base + MX3_TSTAT);
}