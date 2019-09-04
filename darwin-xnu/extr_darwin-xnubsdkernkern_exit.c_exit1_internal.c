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
 int /*<<< orphan*/  OS_REASON_NULL ; 
 int exit_with_reason (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
exit1_internal(proc_t p, int rv, int *retval, boolean_t thread_can_terminate, boolean_t perf_notify,
	       int jetsam_flags)
{
	return exit_with_reason(p, rv, retval, thread_can_terminate, perf_notify, jetsam_flags, OS_REASON_NULL);
}