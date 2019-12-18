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
struct perf_evsel {int /*<<< orphan*/  name; } ;
struct perf_evlist {int dummy; } ;
struct perf_event_attr {int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  perf_evlist__add (struct perf_evlist*,struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__delete (struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__new (struct perf_event_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 

int perf_evlist__add_default(struct perf_evlist *evlist)
{
	struct perf_event_attr attr = {
		.type = PERF_TYPE_HARDWARE,
		.config = PERF_COUNT_HW_CPU_CYCLES,
	};
	struct perf_evsel *evsel;

	event_attr_init(&attr);

	evsel = perf_evsel__new(&attr, 0);
	if (evsel == NULL)
		goto error;

	/* use strdup() because free(evsel) assumes name is allocated */
	evsel->name = strdup("cycles");
	if (!evsel->name)
		goto error_free;

	perf_evlist__add(evlist, evsel);
	return 0;
error_free:
	perf_evsel__delete(evsel);
error:
	return -ENOMEM;
}