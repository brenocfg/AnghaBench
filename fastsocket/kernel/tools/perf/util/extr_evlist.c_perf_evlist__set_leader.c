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
struct perf_evlist {int /*<<< orphan*/  entries; scalar_t__ nr_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_evlist__set_leader (int /*<<< orphan*/ *) ; 

void perf_evlist__set_leader(struct perf_evlist *evlist)
{
	if (evlist->nr_entries)
		__perf_evlist__set_leader(&evlist->entries);
}