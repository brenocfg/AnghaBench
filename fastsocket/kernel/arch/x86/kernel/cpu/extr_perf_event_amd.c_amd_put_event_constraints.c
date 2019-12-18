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
struct hw_perf_event {int dummy; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {struct amd_nb* amd_nb; } ;
struct amd_nb {struct perf_event** owners; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 scalar_t__ amd_has_nb (struct cpu_hw_events*) ; 
 scalar_t__ amd_is_nb_event (struct hw_perf_event*) ; 
 int /*<<< orphan*/  cmpxchg (struct perf_event**,struct perf_event*,int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static void amd_put_event_constraints(struct cpu_hw_events *cpuc,
				      struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct amd_nb *nb = cpuc->amd_nb;
	int i;

	/*
	 * only care about NB events
	 */
	if (!(amd_has_nb(cpuc) && amd_is_nb_event(hwc)))
		return;

	/*
	 * need to scan whole list because event may not have
	 * been assigned during scheduling
	 *
	 * no race condition possible because event can only
	 * be removed on one CPU at a time AND PMU is disabled
	 * when we come here
	 */
	for (i = 0; i < x86_pmu.num_counters; i++) {
		if (nb->owners[i] == event) {
			(void)cmpxchg(nb->owners+i, event, NULL);
			break;
		}
	}
}