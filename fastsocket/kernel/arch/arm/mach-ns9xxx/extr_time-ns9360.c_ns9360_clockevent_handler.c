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
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIS ; 
 int /*<<< orphan*/  INTC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IRQ_NS9360_TIMER0 ; 
 scalar_t__ REGGET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REN ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  SYS_TC (int) ; 
 int /*<<< orphan*/  SYS_TCx ; 
 scalar_t__ SYS_TCx_REN_DIS ; 
 int /*<<< orphan*/  TEN ; 
 int /*<<< orphan*/  UNSET ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clock_event_device ns9360_clockevent_device ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t ns9360_clockevent_handler(int irq, void *dev_id)
{
	int timerno = irq - IRQ_NS9360_TIMER0;
	u32 tc;

	struct clock_event_device *evt = &ns9360_clockevent_device;

	/* clear irq */
	tc = __raw_readl(SYS_TC(timerno));
	if (REGGET(tc, SYS_TCx, REN) == SYS_TCx_REN_DIS) {
		REGSET(tc, SYS_TCx, TEN, DIS);
		__raw_writel(tc, SYS_TC(timerno));
	}
	REGSET(tc, SYS_TCx, INTC, SET);
	__raw_writel(tc, SYS_TC(timerno));
	REGSET(tc, SYS_TCx, INTC, UNSET);
	__raw_writel(tc, SYS_TC(timerno));

	evt->event_handler(evt);

	return IRQ_HANDLED;
}