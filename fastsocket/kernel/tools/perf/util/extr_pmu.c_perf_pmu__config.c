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
struct perf_pmu {int /*<<< orphan*/  format; int /*<<< orphan*/  type; } ;
struct perf_event_attr {int /*<<< orphan*/  type; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int perf_pmu__config_terms (int /*<<< orphan*/ *,struct perf_event_attr*,struct list_head*) ; 

int perf_pmu__config(struct perf_pmu *pmu, struct perf_event_attr *attr,
		     struct list_head *head_terms)
{
	attr->type = pmu->type;
	return perf_pmu__config_terms(&pmu->format, attr, head_terms);
}