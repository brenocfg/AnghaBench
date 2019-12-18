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
struct perf_event_attr {unsigned long bp_addr; scalar_t__ bp_type; int bp_len; int sample_period; int /*<<< orphan*/  type; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int HW_BREAKPOINT_LEN_4 ; 
 scalar_t__ HW_BREAKPOINT_X ; 
 int /*<<< orphan*/  PERF_TYPE_BREAKPOINT ; 
 int add_event (struct list_head**,int*,struct perf_event_attr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_breakpoint_type (char*,struct perf_event_attr*) ; 

int parse_events_add_breakpoint(struct list_head **list, int *idx,
				void *ptr, char *type)
{
	struct perf_event_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.bp_addr = (unsigned long) ptr;

	if (parse_breakpoint_type(type, &attr))
		return -EINVAL;

	/*
	 * We should find a nice way to override the access length
	 * Provide some defaults for now
	 */
	if (attr.bp_type == HW_BREAKPOINT_X)
		attr.bp_len = sizeof(long);
	else
		attr.bp_len = HW_BREAKPOINT_LEN_4;

	attr.type = PERF_TYPE_BREAKPOINT;
	attr.sample_period = 1;

	return add_event(list, idx, &attr, NULL);
}