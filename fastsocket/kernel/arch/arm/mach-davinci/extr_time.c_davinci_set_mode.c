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
struct timer_s {int period; int /*<<< orphan*/  opts; } ;
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int HZ ; 
 size_t TID_CLOCKEVENT ; 
 int /*<<< orphan*/  TIMER_OPTS_DISABLED ; 
 int /*<<< orphan*/  TIMER_OPTS_ONESHOT ; 
 int /*<<< orphan*/  TIMER_OPTS_PERIODIC ; 
 int /*<<< orphan*/  TIMER_OPTS_STATE_MASK ; 
 int davinci_clock_tick_rate ; 
 int /*<<< orphan*/  timer32_config (struct timer_s*) ; 
 struct timer_s* timers ; 

__attribute__((used)) static void davinci_set_mode(enum clock_event_mode mode,
			     struct clock_event_device *evt)
{
	struct timer_s *t = &timers[TID_CLOCKEVENT];

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		t->period = davinci_clock_tick_rate / (HZ);
		t->opts &= ~TIMER_OPTS_STATE_MASK;
		t->opts |= TIMER_OPTS_PERIODIC;
		timer32_config(t);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		t->opts &= ~TIMER_OPTS_STATE_MASK;
		t->opts |= TIMER_OPTS_ONESHOT;
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		t->opts &= ~TIMER_OPTS_STATE_MASK;
		t->opts |= TIMER_OPTS_DISABLED;
		break;
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}