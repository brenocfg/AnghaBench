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
struct perf_evsel {int /*<<< orphan*/ * fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__close_fd (struct perf_evsel*,int,int) ; 
 int /*<<< orphan*/  perf_evsel__free_fd (struct perf_evsel*) ; 

void perf_evsel__close(struct perf_evsel *evsel, int ncpus, int nthreads)
{
	if (evsel->fd == NULL)
		return;

	perf_evsel__close_fd(evsel, ncpus, nthreads);
	perf_evsel__free_fd(evsel);
	evsel->fd = NULL;
}