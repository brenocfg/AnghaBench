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
struct perf_evsel {int /*<<< orphan*/  node; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  free (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct list_head* malloc (int) ; 
 struct perf_evsel* perf_evsel__newtp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_tracepoint(struct list_head **listp, int *idx,
			  char *sys_name, char *evt_name)
{
	struct perf_evsel *evsel;
	struct list_head *list = *listp;

	if (!list) {
		list = malloc(sizeof(*list));
		if (!list)
			return -ENOMEM;
		INIT_LIST_HEAD(list);
	}

	evsel = perf_evsel__newtp(sys_name, evt_name, (*idx)++);
	if (!evsel) {
		free(list);
		return -ENOMEM;
	}

	list_add_tail(&evsel->node, list);
	*listp = list;
	return 0;
}