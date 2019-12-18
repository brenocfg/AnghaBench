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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TIMER_CTRL ; 
 unsigned long TIMER_CTRL_ENABLE ; 
 scalar_t__ TIMER_LOAD ; 
 unsigned long readl (scalar_t__) ; 
 scalar_t__ timer0_va_base ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int timer_set_next_event(unsigned long evt,
				struct clock_event_device *unused)
{
	unsigned long ctrl = readl(timer0_va_base + TIMER_CTRL);

	writel(evt, timer0_va_base + TIMER_LOAD);
	writel(ctrl | TIMER_CTRL_ENABLE, timer0_va_base + TIMER_CTRL);

	return 0;
}