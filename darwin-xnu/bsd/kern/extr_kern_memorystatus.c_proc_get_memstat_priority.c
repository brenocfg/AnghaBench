#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int p_memstat_effectivepriority; int p_memstat_requestedpriority; } ;

/* Variables and functions */

int
proc_get_memstat_priority(proc_t p, boolean_t effective_priority)
{
	if (p) {
		if (effective_priority) {
			return p->p_memstat_effectivepriority;
		} else {
			return p->p_memstat_requestedpriority;
		}
	}
	return 0;
}