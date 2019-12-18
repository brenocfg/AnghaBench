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
 scalar_t__ TWD_TIMER_CONTROL ; 
 unsigned long TWD_TIMER_CONTROL_ENABLE ; 
 scalar_t__ TWD_TIMER_COUNTER ; 
 unsigned long __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 scalar_t__ twd_base ; 

__attribute__((used)) static int twd_set_next_event(unsigned long evt,
			struct clock_event_device *unused)
{
	unsigned long ctrl = __raw_readl(twd_base + TWD_TIMER_CONTROL);

	ctrl |= TWD_TIMER_CONTROL_ENABLE;

	__raw_writel(evt, twd_base + TWD_TIMER_COUNTER);
	__raw_writel(ctrl, twd_base + TWD_TIMER_CONTROL);

	return 0;
}