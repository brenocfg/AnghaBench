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
struct perf_pmu {int /*<<< orphan*/  cpus; } ;
struct perf_event_attr {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int __add_event (struct list_head**,int*,struct perf_event_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_attr (struct perf_event_attr*,struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ perf_pmu__check_alias (struct perf_pmu*,struct list_head*) ; 
 scalar_t__ perf_pmu__config (struct perf_pmu*,struct perf_event_attr*,struct list_head*) ; 
 struct perf_pmu* perf_pmu__find (char*) ; 
 int /*<<< orphan*/  pmu_event_name (struct list_head*) ; 

int parse_events_add_pmu(struct list_head **list, int *idx,
			 char *name, struct list_head *head_config)
{
	struct perf_event_attr attr;
	struct perf_pmu *pmu;

	pmu = perf_pmu__find(name);
	if (!pmu)
		return -EINVAL;

	memset(&attr, 0, sizeof(attr));

	if (perf_pmu__check_alias(pmu, head_config))
		return -EINVAL;

	/*
	 * Configure hardcoded terms first, no need to check
	 * return value when called with fail == 0 ;)
	 */
	config_attr(&attr, head_config, 0);

	if (perf_pmu__config(pmu, &attr, head_config))
		return -EINVAL;

	return __add_event(list, idx, &attr, pmu_event_name(head_config),
			   pmu->cpus);
}