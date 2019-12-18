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
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 int FD (struct perf_evsel*,int,int) ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_SET_FILTER ; 
 int ioctl (int,int /*<<< orphan*/ ,char const*) ; 

int perf_evsel__set_filter(struct perf_evsel *evsel, int ncpus, int nthreads,
			   const char *filter)
{
	int cpu, thread;

	for (cpu = 0; cpu < ncpus; cpu++) {
		for (thread = 0; thread < nthreads; thread++) {
			int fd = FD(evsel, cpu, thread),
			    err = ioctl(fd, PERF_EVENT_IOC_SET_FILTER, filter);

			if (err)
				return err;
		}
	}

	return 0;
}