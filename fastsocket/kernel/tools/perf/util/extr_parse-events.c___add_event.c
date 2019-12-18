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
struct perf_evsel {int /*<<< orphan*/  node; int /*<<< orphan*/  name; struct cpu_map* cpus; } ;
struct perf_event_attr {int dummy; } ;
struct list_head {int dummy; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  free (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct list_head* malloc (int) ; 
 struct perf_evsel* perf_evsel__new (struct perf_event_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int __add_event(struct list_head **_list, int *idx,
		       struct perf_event_attr *attr,
		       char *name, struct cpu_map *cpus)
{
	struct perf_evsel *evsel;
	struct list_head *list = *_list;

	if (!list) {
		list = malloc(sizeof(*list));
		if (!list)
			return -ENOMEM;
		INIT_LIST_HEAD(list);
	}

	event_attr_init(attr);

	evsel = perf_evsel__new(attr, (*idx)++);
	if (!evsel) {
		free(list);
		return -ENOMEM;
	}

	evsel->cpus = cpus;
	if (name)
		evsel->name = strdup(name);
	list_add_tail(&evsel->node, list);
	*_list = list;
	return 0;
}