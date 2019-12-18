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
typedef  int u64 ;
struct perf_event {int dummy; } ;
struct hw_perf_event {int sample_period; int last_period; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  period_left; } ;
typedef  int s64 ;

/* Variables and functions */
 int MAX_PERIOD ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_pmc (int,int) ; 

__attribute__((used)) static int sparc_perf_event_set_period(struct perf_event *event,
				       struct hw_perf_event *hwc, int idx)
{
	s64 left = atomic64_read(&hwc->period_left);
	s64 period = hwc->sample_period;
	int ret = 0;

	if (unlikely(left <= -period)) {
		left = period;
		atomic64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	}

	if (unlikely(left <= 0)) {
		left += period;
		atomic64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	}
	if (left > MAX_PERIOD)
		left = MAX_PERIOD;

	atomic64_set(&hwc->prev_count, (u64)-left);

	write_pmc(idx, (u64)(-left) & 0xffffffff);

	perf_event_update_userpage(event);

	return ret;
}