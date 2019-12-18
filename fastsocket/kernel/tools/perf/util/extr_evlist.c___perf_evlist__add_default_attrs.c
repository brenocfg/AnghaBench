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
struct perf_evlist {int dummy; } ;
struct perf_event_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int perf_evlist__add_attrs (struct perf_evlist*,struct perf_event_attr*,size_t) ; 

int __perf_evlist__add_default_attrs(struct perf_evlist *evlist,
				     struct perf_event_attr *attrs, size_t nr_attrs)
{
	size_t i;

	for (i = 0; i < nr_attrs; i++)
		event_attr_init(attrs + i);

	return perf_evlist__add_attrs(evlist, attrs, nr_attrs);
}