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
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  Call_continuation (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
call_continuation(
	thread_continue_t continuation,
	void *parameter,
	wait_result_t wresult,
	boolean_t enable_interrupts)
{
#define call_continuation_kprintf(x...)	/* kprintf("call_continuation_kprintf:" x) */

	call_continuation_kprintf("thread = %p continuation = %p, stack = %p\n", current_thread(), continuation, current_thread()->machine.kstackptr);
	Call_continuation(continuation, parameter, wresult, enable_interrupts);
}