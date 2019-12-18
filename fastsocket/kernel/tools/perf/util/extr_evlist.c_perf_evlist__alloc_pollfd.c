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
struct pollfd {int dummy; } ;
struct perf_evlist {int nr_entries; int /*<<< orphan*/ * pollfd; TYPE_1__* threads; int /*<<< orphan*/  cpus; } ;
struct TYPE_2__ {int nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int cpu_map__nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static int perf_evlist__alloc_pollfd(struct perf_evlist *evlist)
{
	int nfds = cpu_map__nr(evlist->cpus) * evlist->threads->nr * evlist->nr_entries;
	evlist->pollfd = malloc(sizeof(struct pollfd) * nfds);
	return evlist->pollfd != NULL ? 0 : -ENOMEM;
}