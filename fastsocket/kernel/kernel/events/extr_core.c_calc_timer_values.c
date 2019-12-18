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
typedef  scalar_t__ u64 ;
struct perf_event {scalar_t__ tstamp_running; scalar_t__ tstamp_enabled; scalar_t__ shadow_ctx_time; } ;

/* Variables and functions */
 scalar_t__ perf_clock () ; 

__attribute__((used)) static void calc_timer_values(struct perf_event *event,
				u64 *enabled,
				u64 *running)
{
	u64 now, ctx_time;

	now = perf_clock();
	ctx_time = event->shadow_ctx_time + now;
	*enabled = ctx_time - event->tstamp_enabled;
	*running = ctx_time - event->tstamp_running;
}