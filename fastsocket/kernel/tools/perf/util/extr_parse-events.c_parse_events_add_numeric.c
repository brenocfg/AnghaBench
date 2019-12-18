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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct perf_event_attr {int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int add_event (struct list_head**,int*,struct perf_event_attr*,int /*<<< orphan*/ *) ; 
 scalar_t__ config_attr (struct perf_event_attr*,struct list_head*,int) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 

int parse_events_add_numeric(struct list_head **list, int *idx,
			     u32 type, u64 config,
			     struct list_head *head_config)
{
	struct perf_event_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.type = type;
	attr.config = config;

	if (head_config &&
	    config_attr(&attr, head_config, 1))
		return -EINVAL;

	return add_event(list, idx, &attr, NULL);
}