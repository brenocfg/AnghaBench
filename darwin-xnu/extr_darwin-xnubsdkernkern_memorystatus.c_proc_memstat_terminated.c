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
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */

void
proc_memstat_terminated(proc_t p, boolean_t set)
{
#if DEVELOPMENT || DEBUG
	if (p) {
		proc_list_lock();
		if (set == TRUE) {
			p->p_memstat_state |= P_MEMSTAT_TERMINATED;
		} else {
			p->p_memstat_state &= ~P_MEMSTAT_TERMINATED;
		}
		proc_list_unlock();
	}
#else
#pragma unused(p, set)
	/*
	 * do nothing
	 */
#endif /* DEVELOPMENT || DEBUG */
	return;
}