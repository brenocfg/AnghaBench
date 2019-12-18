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
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 unsigned int COUNTEN ; 
 unsigned int INTEN ; 
 unsigned int ONESHOT ; 
 unsigned int PERIOD ; 
 unsigned int PRESCALE ; 
 int /*<<< orphan*/  REG_TCSR0 ; 
 int /*<<< orphan*/  REG_TICR0 ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int timer0_load ; 

__attribute__((used)) static void nuc900_clockevent_setmode(enum clock_event_mode mode,
		struct clock_event_device *clk)
{
	unsigned int val;

	val = __raw_readl(REG_TCSR0);
	val &= ~(0x03 << 27);

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		__raw_writel(timer0_load, REG_TICR0);
		val |= (PERIOD | COUNTEN | INTEN | PRESCALE);
		break;

	case CLOCK_EVT_MODE_ONESHOT:
		val |= (ONESHOT | COUNTEN | INTEN | PRESCALE);
		break;

	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_RESUME:
		break;
	}

	__raw_writel(val, REG_TCSR0);
}