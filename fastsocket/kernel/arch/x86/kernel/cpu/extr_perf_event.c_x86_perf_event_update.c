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
typedef  int u64 ;
struct hw_perf_event {int idx; int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  event_base; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;
typedef  int s64 ;
struct TYPE_2__ {int cntval_bits; } ;

/* Variables and functions */
 int X86_PMC_IDX_FIXED_BTS ; 
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ x86_pmu ; 

u64 x86_perf_event_update(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	int shift = 64 - x86_pmu.cntval_bits;
	u64 prev_raw_count, new_raw_count;
	int idx = hwc->idx;
	s64 delta;

	if (idx == X86_PMC_IDX_FIXED_BTS)
		return 0;

	/*
	 * Careful: an NMI might modify the previous event value.
	 *
	 * Our tactic to handle this is to first atomically read and
	 * exchange a new raw count - then add that new-prev delta
	 * count to the generic event atomically:
	 */
again:
	prev_raw_count = local64_read(&hwc->prev_count);
	rdmsrl(hwc->event_base, new_raw_count);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
					new_raw_count) != prev_raw_count)
		goto again;

	/*
	 * Now we have the new raw value and have updated the prev
	 * timestamp already. We can now calculate the elapsed delta
	 * (event-)time and add that to the generic event.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shift) - (prev_raw_count << shift);
	delta >>= shift;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	return new_raw_count;
}