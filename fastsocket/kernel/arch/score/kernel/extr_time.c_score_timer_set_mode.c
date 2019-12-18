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
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int HZ ; 
 int /*<<< orphan*/  P_TIMER0_CTRL ; 
 int /*<<< orphan*/  P_TIMER0_PRELOAD ; 
 int SYSTEM_CLOCK ; 
 int TMR_ENABLE ; 
 int TMR_IE_ENABLE ; 
 int TMR_M_PERIODIC ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void score_timer_set_mode(enum clock_event_mode mode,
		struct clock_event_device *evdev)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		outl((TMR_M_PERIODIC | TMR_IE_ENABLE), P_TIMER0_CTRL);
		outl(SYSTEM_CLOCK/HZ, P_TIMER0_PRELOAD);
		outl(inl(P_TIMER0_CTRL) | TMR_ENABLE, P_TIMER0_CTRL);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_RESUME:
	case CLOCK_EVT_MODE_UNUSED:
		break;
	default:
		BUG();
	}
}