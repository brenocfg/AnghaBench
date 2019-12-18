#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ event_id; char* name; } ;

/* Variables and functions */
 int trace_event_count ; 
 TYPE_1__* trace_events ; 

char *perf_header__find_event(u64 id)
{
	int i;
	for (i = 0 ; i < trace_event_count; i++) {
		if (trace_events[i].event_id == id)
			return trace_events[i].name;
	}
	return NULL;
}