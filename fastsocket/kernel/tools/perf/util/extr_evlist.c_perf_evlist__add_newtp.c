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
struct TYPE_2__ {void* func; } ;
struct perf_evsel {TYPE_1__ handler; } ;
struct perf_evlist {int /*<<< orphan*/  nr_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__add (struct perf_evlist*,struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__newtp (char const*,char const*,int /*<<< orphan*/ ) ; 

int perf_evlist__add_newtp(struct perf_evlist *evlist,
			   const char *sys, const char *name, void *handler)
{
	struct perf_evsel *evsel;

	evsel = perf_evsel__newtp(sys, name, evlist->nr_entries);
	if (evsel == NULL)
		return -1;

	evsel->handler.func = handler;
	perf_evlist__add(evlist, evsel);
	return 0;
}