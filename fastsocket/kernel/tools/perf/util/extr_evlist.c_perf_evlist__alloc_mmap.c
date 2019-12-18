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
struct perf_mmap {int dummy; } ;
struct perf_evlist {int nr_mmaps; int /*<<< orphan*/ * mmap; TYPE_1__* threads; int /*<<< orphan*/  cpus; } ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ cpu_map__all (int /*<<< orphan*/ ) ; 
 int cpu_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zalloc (int) ; 

__attribute__((used)) static int perf_evlist__alloc_mmap(struct perf_evlist *evlist)
{
	evlist->nr_mmaps = cpu_map__nr(evlist->cpus);
	if (cpu_map__all(evlist->cpus))
		evlist->nr_mmaps = evlist->threads->nr;
	evlist->mmap = zalloc(evlist->nr_mmaps * sizeof(struct perf_mmap));
	return evlist->mmap != NULL ? 0 : -ENOMEM;
}