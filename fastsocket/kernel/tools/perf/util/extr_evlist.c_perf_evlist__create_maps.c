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
struct perf_target {int /*<<< orphan*/  cpu_list; int /*<<< orphan*/  uses_mmap; int /*<<< orphan*/  uid; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct perf_evlist {int /*<<< orphan*/ * threads; int /*<<< orphan*/ * cpus; } ;

/* Variables and functions */
 void* cpu_map__dummy_new () ; 
 int /*<<< orphan*/ * cpu_map__new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_target__has_cpu (struct perf_target*) ; 
 scalar_t__ perf_target__has_task (struct perf_target*) ; 
 int /*<<< orphan*/  thread_map__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * thread_map__new_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int perf_evlist__create_maps(struct perf_evlist *evlist,
			     struct perf_target *target)
{
	evlist->threads = thread_map__new_str(target->pid, target->tid,
					      target->uid);

	if (evlist->threads == NULL)
		return -1;

	if (perf_target__has_task(target))
		evlist->cpus = cpu_map__dummy_new();
	else if (!perf_target__has_cpu(target) && !target->uses_mmap)
		evlist->cpus = cpu_map__dummy_new();
	else
		evlist->cpus = cpu_map__new(target->cpu_list);

	if (evlist->cpus == NULL)
		goto out_delete_threads;

	return 0;

out_delete_threads:
	thread_map__delete(evlist->threads);
	return -1;
}