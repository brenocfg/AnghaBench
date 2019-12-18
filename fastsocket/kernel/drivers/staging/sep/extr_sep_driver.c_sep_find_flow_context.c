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
struct sep_flow_context_t {unsigned long flow_id; } ;
struct sep_device {struct sep_flow_context_t* flows; } ;

/* Variables and functions */
 int SEP_DRIVER_NUM_FLOWS ; 

__attribute__((used)) static struct sep_flow_context_t *sep_find_flow_context(struct sep_device *sep,
				unsigned long flow_id)
{
	int count;
	/*
	 *  always search for flow with id default first - in case we
	 *  already started working on the flow there can be no situation
	 *  when 2 flows are with default flag
	 */
	for (count = 0; count < SEP_DRIVER_NUM_FLOWS; count++) {
		if (sep->flows[count].flow_id == flow_id)
			return &sep->flows[count];
	}
	return NULL;
}