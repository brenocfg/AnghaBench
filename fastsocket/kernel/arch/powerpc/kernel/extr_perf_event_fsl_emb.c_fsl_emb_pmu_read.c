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
struct TYPE_2__ {int state; int /*<<< orphan*/  period_left; int /*<<< orphan*/  idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  count; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ read_pmc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_emb_pmu_read(struct perf_event *event)
{
	s64 val, delta, prev;

	if (event->hw.state & PERF_HES_STOPPED)
		return;

	/*
	 * Performance monitor interrupts come even when interrupts
	 * are soft-disabled, as long as interrupts are hard-enabled.
	 * Therefore we treat them like NMIs.
	 */
	do {
		prev = local64_read(&event->hw.prev_count);
		barrier();
		val = read_pmc(event->hw.idx);
	} while (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	/* The counters are only 32 bits wide */
	delta = (val - prev) & 0xfffffffful;
	local64_add(delta, &event->count);
	local64_sub(delta, &event->hw.period_left);
}