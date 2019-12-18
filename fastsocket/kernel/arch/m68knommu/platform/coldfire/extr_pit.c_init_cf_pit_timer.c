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
 int /*<<< orphan*/  MCFPIT_PCSR ; 
 int MCFPIT_PCSR_CLK64 ; 
 int MCFPIT_PCSR_DISABLE ; 
 int MCFPIT_PCSR_EN ; 
 int MCFPIT_PCSR_OVW ; 
 int MCFPIT_PCSR_PIE ; 
 int MCFPIT_PCSR_RLD ; 
 int /*<<< orphan*/  MCFPIT_PMR ; 
 int PIT_CYCLES_PER_JIFFY ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_cf_pit_timer(enum clock_event_mode mode,
                             struct clock_event_device *evt)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:

		__raw_writew(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
		__raw_writew(PIT_CYCLES_PER_JIFFY, TA(MCFPIT_PMR));
		__raw_writew(MCFPIT_PCSR_EN | MCFPIT_PCSR_PIE | \
				MCFPIT_PCSR_OVW | MCFPIT_PCSR_RLD | \
				MCFPIT_PCSR_CLK64, TA(MCFPIT_PCSR));
		break;

	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:

		__raw_writew(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
		break;

	case CLOCK_EVT_MODE_ONESHOT:

		__raw_writew(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
		__raw_writew(MCFPIT_PCSR_EN | MCFPIT_PCSR_PIE | \
				MCFPIT_PCSR_OVW | MCFPIT_PCSR_CLK64, \
				TA(MCFPIT_PCSR));
		break;

	case CLOCK_EVT_MODE_RESUME:
		/* Nothing to do here */
		break;
	}
}