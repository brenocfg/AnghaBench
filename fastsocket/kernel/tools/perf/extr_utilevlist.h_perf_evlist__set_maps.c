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
struct thread_map {int dummy; } ;
struct perf_evlist {struct thread_map* threads; struct cpu_map* cpus; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void perf_evlist__set_maps(struct perf_evlist *evlist,
					 struct cpu_map *cpus,
					 struct thread_map *threads)
{
	evlist->cpus	= cpus;
	evlist->threads	= threads;
}