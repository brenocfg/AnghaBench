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
 int __perf_evsel__read (struct perf_evsel*,int,int,int) ; 

__attribute__((used)) static inline int perf_evsel__read_scaled(struct perf_evsel *evsel,
					  int ncpus, int nthreads)
{
	return __perf_evsel__read(evsel, ncpus, nthreads, true);
}