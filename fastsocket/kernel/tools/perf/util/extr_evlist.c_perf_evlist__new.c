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
struct perf_evlist {int dummy; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__init (struct perf_evlist*,struct cpu_map*,struct thread_map*) ; 
 struct perf_evlist* zalloc (int) ; 

struct perf_evlist *perf_evlist__new(struct cpu_map *cpus,
				     struct thread_map *threads)
{
	struct perf_evlist *evlist = zalloc(sizeof(*evlist));

	if (evlist != NULL)
		perf_evlist__init(evlist, cpus, threads);

	return evlist;
}