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
typedef  int u_int ;

/* Variables and functions */
 scalar_t__ IF_Mbps (int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * hc_update_timer ; 
 int mibif_force_hc_update_interval ; 
 int mibif_hc_update_interval ; 
 scalar_t__ mibif_maxspeed ; 
 int /*<<< orphan*/  module ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * timer_start_repeat (int,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_hc_counters (int /*<<< orphan*/ *) ; 

void
mibif_reset_hc_timer(void)
{
	u_int ticks;

	if ((ticks = mibif_force_hc_update_interval) == 0) {
		if (mibif_maxspeed <= IF_Mbps(10)) {
			/* at 10Mbps overflow needs 3436 seconds */
			ticks = 3000 * 100;	/* 50 minutes */
		} else if (mibif_maxspeed <= IF_Mbps(100)) {
			/* at 100Mbps overflow needs 343 seconds */
			ticks = 300 * 100;	/* 5 minutes */
		} else if (mibif_maxspeed < IF_Mbps(622)) {
			/* at 622Mbps overflow needs 53 seconds */
			ticks = 40 * 100;	/* 40 seconds */
		} else if (mibif_maxspeed <= IF_Mbps(1000)) {
			/* at 1Gbps overflow needs  34 seconds */
			ticks = 20 * 100;	/* 20 seconds */
		} else {
			/* at 10Gbps overflow needs 3.4 seconds */
			ticks = 100;		/* 1 seconds */
		}
	}

	if (ticks == mibif_hc_update_interval)
		return;

	if (hc_update_timer != NULL) {
		timer_stop(hc_update_timer);
		hc_update_timer = NULL;
	}
	update_hc_counters(NULL);
	if ((hc_update_timer = timer_start_repeat(ticks, ticks,
	    update_hc_counters, NULL, module)) == NULL) {
		syslog(LOG_ERR, "timer_start(%u): %m", ticks);
		return;
	}
	mibif_hc_update_interval = ticks;
}