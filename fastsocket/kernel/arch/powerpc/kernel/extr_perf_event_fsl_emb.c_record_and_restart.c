#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int /*<<< orphan*/  period; } ;
struct TYPE_2__ {unsigned long sample_period; int state; int /*<<< orphan*/  last_period; int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  idx; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  count; } ;
typedef  unsigned long s64 ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int /*<<< orphan*/  fsl_emb_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local64_add (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pmc (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void record_and_restart(struct perf_event *event, unsigned long val,
			       struct pt_regs *regs)
{
	u64 period = event->hw.sample_period;
	s64 prev, delta, left;
	int record = 0;

	if (event->hw.state & PERF_HES_STOPPED) {
		write_pmc(event->hw.idx, 0);
		return;
	}

	/* we don't have to worry about interrupts here */
	prev = local64_read(&event->hw.prev_count);
	delta = (val - prev) & 0xfffffffful;
	local64_add(delta, &event->count);

	/*
	 * See if the total period for this event has expired,
	 * and update for the next period.
	 */
	val = 0;
	left = local64_read(&event->hw.period_left) - delta;
	if (period) {
		if (left <= 0) {
			left += period;
			if (left <= 0)
				left = period;
			record = 1;
		}
		if (left < 0x80000000LL)
			val = 0x80000000LL - left;
	}

	write_pmc(event->hw.idx, val);
	local64_set(&event->hw.prev_count, val);
	local64_set(&event->hw.period_left, left);
	perf_event_update_userpage(event);

	/*
	 * Finally record data if requested.
	 */
	if (record) {
		struct perf_sample_data data;

		perf_sample_data_init(&data, 0);
		data.period = event->hw.last_period;

		if (perf_event_overflow(event, &data, regs))
			fsl_emb_pmu_stop(event, 0);
	}
}