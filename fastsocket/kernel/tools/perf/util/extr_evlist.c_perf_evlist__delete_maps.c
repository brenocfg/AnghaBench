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
struct perf_evlist {int /*<<< orphan*/ * threads; int /*<<< orphan*/ * cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_map__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_map__delete (int /*<<< orphan*/ *) ; 

void perf_evlist__delete_maps(struct perf_evlist *evlist)
{
	cpu_map__delete(evlist->cpus);
	thread_map__delete(evlist->threads);
	evlist->cpus	= NULL;
	evlist->threads = NULL;
}