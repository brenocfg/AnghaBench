#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_map {int dummy; } ;
struct perf_evsel {int dummy; } ;
struct cpu_map {int dummy; } ;
struct TYPE_4__ {struct cpu_map map; } ;
struct TYPE_3__ {struct thread_map map; } ;

/* Variables and functions */
 int __perf_evsel__open (struct perf_evsel*,struct cpu_map*,struct thread_map*) ; 
 TYPE_2__ empty_cpu_map ; 
 TYPE_1__ empty_thread_map ; 

int perf_evsel__open(struct perf_evsel *evsel, struct cpu_map *cpus,
		     struct thread_map *threads)
{
	if (cpus == NULL) {
		/* Work around old compiler warnings about strict aliasing */
		cpus = &empty_cpu_map.map;
	}

	if (threads == NULL)
		threads = &empty_thread_map.map;

	return __perf_evsel__open(evsel, cpus, threads);
}