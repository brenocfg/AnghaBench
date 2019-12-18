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
struct TYPE_2__ {int config; scalar_t__ type; } ;
struct perf_event {int /*<<< orphan*/  destroy; int /*<<< orphan*/  parent; TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOENT ; 
#define  PERF_COUNT_SW_CPU_CLOCK 129 
 int PERF_COUNT_SW_MAX ; 
#define  PERF_COUNT_SW_TASK_CLOCK 128 
 scalar_t__ PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * perf_swevent_enabled ; 
 int /*<<< orphan*/  sw_perf_event_destroy ; 
 int swevent_hlist_get (struct perf_event*) ; 

__attribute__((used)) static int perf_swevent_init(struct perf_event *event)
{
	u64 event_id = event->attr.config;

	if (event->attr.type != PERF_TYPE_SOFTWARE)
		return -ENOENT;

	switch (event_id) {
	case PERF_COUNT_SW_CPU_CLOCK:
	case PERF_COUNT_SW_TASK_CLOCK:
		return -ENOENT;

	default:
		break;
	}

	if (event_id >= PERF_COUNT_SW_MAX)
		return -ENOENT;

	if (!event->parent) {
		int err;

		err = swevent_hlist_get(event);
		if (err)
			return err;

		atomic_inc(&perf_swevent_enabled[event_id]);
		event->destroy = sw_perf_event_destroy;
	}

	return 0;
}