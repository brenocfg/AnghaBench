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
typedef  int u32 ;
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int HZ ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_is_omap44xx () ; 
 int /*<<< orphan*/  gptimer ; 
 int /*<<< orphan*/  omap_dm_timer_get_fclk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dm_timer_set_load_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dm_timer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_gp_timer_set_mode(enum clock_event_mode mode,
				    struct clock_event_device *evt)
{
	u32 period;

	omap_dm_timer_stop(gptimer);

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		period = clk_get_rate(omap_dm_timer_get_fclk(gptimer)) / HZ;
		period -= 1;
		if (cpu_is_omap44xx())
			period = 0xff;	/* FIXME: */
		omap_dm_timer_set_load_start(gptimer, 1, 0xffffffff - period);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}