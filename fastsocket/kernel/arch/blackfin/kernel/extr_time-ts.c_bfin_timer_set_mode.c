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
 int /*<<< orphan*/  CSYNC () ; 
 int HZ ; 
 int TAUTORLD ; 
 int TIME_SCALE ; 
 int TMPWR ; 
 int TMREN ; 
 int /*<<< orphan*/  bfin_write_TCNTL (int) ; 
 int /*<<< orphan*/  bfin_write_TCOUNT (unsigned long) ; 
 int /*<<< orphan*/  bfin_write_TPERIOD (unsigned long) ; 
 int /*<<< orphan*/  bfin_write_TSCALE (int /*<<< orphan*/ ) ; 
 int get_cclk () ; 

__attribute__((used)) static void bfin_timer_set_mode(enum clock_event_mode mode,
				struct clock_event_device *evt)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC: {
		unsigned long tcount = ((get_cclk() / (HZ * TIME_SCALE)) - 1);
		bfin_write_TCNTL(TMPWR);
		CSYNC();
		bfin_write_TSCALE(TIME_SCALE - 1);
		bfin_write_TPERIOD(tcount);
		bfin_write_TCOUNT(tcount);
		CSYNC();
		bfin_write_TCNTL(TMPWR | TMREN | TAUTORLD);
		break;
	}
	case CLOCK_EVT_MODE_ONESHOT:
		bfin_write_TCNTL(TMPWR);
		CSYNC();
		bfin_write_TSCALE(TIME_SCALE - 1);
		bfin_write_TPERIOD(0);
		bfin_write_TCOUNT(0);
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		bfin_write_TCNTL(0);
		CSYNC();
		break;
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}