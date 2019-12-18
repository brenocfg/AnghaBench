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
struct perf_evsel {struct perf_evsel* name; scalar_t__ tp_format; struct perf_evsel* group_name; int /*<<< orphan*/  cgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_cgroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct perf_evsel*) ; 
 int /*<<< orphan*/  perf_evsel__exit (struct perf_evsel*) ; 
 int /*<<< orphan*/  pevent_free_format (scalar_t__) ; 

void perf_evsel__delete(struct perf_evsel *evsel)
{
	perf_evsel__exit(evsel);
	close_cgroup(evsel->cgrp);
	free(evsel->group_name);
	if (evsel->tp_format)
		pevent_free_format(evsel->tp_format);
	free(evsel->name);
	free(evsel);
}