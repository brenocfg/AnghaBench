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
typedef  unsigned long u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIS ; 
 int /*<<< orphan*/  EN ; 
 scalar_t__ REGGET (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGSET (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_TC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_TCx ; 
 int /*<<< orphan*/  SYS_TRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEN ; 
 int /*<<< orphan*/  TIMER_CLOCKEVENT ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns9360_clockevent_setnextevent(unsigned long evt,
		struct clock_event_device *clk)
{
	u32 tc = __raw_readl(SYS_TC(TIMER_CLOCKEVENT));

	if (REGGET(tc, SYS_TCx, TEN)) {
		REGSET(tc, SYS_TCx, TEN, DIS);
		__raw_writel(tc, SYS_TC(TIMER_CLOCKEVENT));
	}

	REGSET(tc, SYS_TCx, TEN, EN);

	__raw_writel(evt, SYS_TRC(TIMER_CLOCKEVENT));

	__raw_writel(tc, SYS_TC(TIMER_CLOCKEVENT));

	return 0;
}