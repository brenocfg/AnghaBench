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
struct test__event_st {int (* check ) (struct perf_evlist*) ;int /*<<< orphan*/  name; } ;
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int parse_events (struct perf_evlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__delete (struct perf_evlist*) ; 
 struct perf_evlist* perf_evlist__new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct perf_evlist*) ; 

__attribute__((used)) static int test_event(struct test__event_st *e)
{
	struct perf_evlist *evlist;
	int ret;

	evlist = perf_evlist__new(NULL, NULL);
	if (evlist == NULL)
		return -ENOMEM;

	ret = parse_events(evlist, e->name, 0);
	if (ret) {
		pr_debug("failed to parse event '%s', err %d\n",
			 e->name, ret);
		return ret;
	}

	ret = e->check(evlist);
	perf_evlist__delete(evlist);

	return ret;
}