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
struct hw_perf_event {int /*<<< orphan*/  idx; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  sparc_perf_event_update (struct perf_event*,struct hw_perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sparc_pmu_read(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	sparc_perf_event_update(event, hwc, hwc->idx);
}