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
struct TYPE_2__ {scalar_t__ size; } ;
struct perf_evsel {struct perf_evsel* id; struct perf_evsel* name; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct perf_evsel*) ; 

__attribute__((used)) static void free_event_desc(struct perf_evsel *events)
{
	struct perf_evsel *evsel;

	if (!events)
		return;

	for (evsel = events; evsel->attr.size; evsel++) {
		if (evsel->name)
			free(evsel->name);
		if (evsel->id)
			free(evsel->id);
	}

	free(events);
}