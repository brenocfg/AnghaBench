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
struct perf_evlist {int nr_entries; int /*<<< orphan*/  entries; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail (struct list_head*,int /*<<< orphan*/ *) ; 

void perf_evlist__splice_list_tail(struct perf_evlist *evlist,
				   struct list_head *list,
				   int nr_entries)
{
	list_splice_tail(list, &evlist->entries);
	evlist->nr_entries += nr_entries;
}