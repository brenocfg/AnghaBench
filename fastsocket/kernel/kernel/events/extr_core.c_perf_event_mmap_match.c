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
struct perf_mmap_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ mmap; scalar_t__ mmap_data; } ;
struct perf_event {scalar_t__ state; TYPE_1__ attr; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_INACTIVE ; 
 int /*<<< orphan*/  event_filter_match (struct perf_event*) ; 

__attribute__((used)) static int perf_event_mmap_match(struct perf_event *event,
				   struct perf_mmap_event *mmap_event,
				   int executable)
{
	if (event->state < PERF_EVENT_STATE_INACTIVE)
		return 0;

	if (!event_filter_match(event))
		return 0;

	if ((!executable && event->attr.mmap_data) ||
	    (executable && event->attr.mmap))
		return 1;

	return 0;
}