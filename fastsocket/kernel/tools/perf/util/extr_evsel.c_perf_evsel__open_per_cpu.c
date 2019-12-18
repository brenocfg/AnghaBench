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
struct perf_evsel {int dummy; } ;
struct cpu_map {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int __perf_evsel__open (struct perf_evsel*,struct cpu_map*,int /*<<< orphan*/ *) ; 
 TYPE_1__ empty_thread_map ; 

int perf_evsel__open_per_cpu(struct perf_evsel *evsel,
			     struct cpu_map *cpus)
{
	return __perf_evsel__open(evsel, cpus, &empty_thread_map.map);
}