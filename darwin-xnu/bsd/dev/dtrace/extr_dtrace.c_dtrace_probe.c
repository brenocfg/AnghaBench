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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 scalar_t__ DTRACEFLT_UNKNOWN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __dtrace_probe (scalar_t__,scalar_t__,scalar_t__,int,int,scalar_t__) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  dtrace_get_thread_reentering (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_getipl () ; 
 scalar_t__ dtrace_probeid_error ; 
 int /*<<< orphan*/  dtrace_set_thread_reentering (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_preemption () ; 

void
dtrace_probe(dtrace_id_t id, uint64_t arg0, uint64_t arg1,
    uint64_t arg2, uint64_t arg3, uint64_t arg4)
{
	thread_t thread = current_thread();
	disable_preemption();
	if (id == dtrace_probeid_error) {
		__dtrace_probe(id, arg0, arg1, arg2, arg3, arg4);
		dtrace_getipl(); /* Defeat tail-call optimization of __dtrace_probe() */
	} else if (!dtrace_get_thread_reentering(thread)) {
		dtrace_set_thread_reentering(thread, TRUE);
		__dtrace_probe(id, arg0, arg1, arg2, arg3, arg4);
		dtrace_set_thread_reentering(thread, FALSE);
	}
#if DEBUG
	else __dtrace_probe(dtrace_probeid_error, 0, id, 1, -1, DTRACEFLT_UNKNOWN);
#endif
	enable_preemption();
}