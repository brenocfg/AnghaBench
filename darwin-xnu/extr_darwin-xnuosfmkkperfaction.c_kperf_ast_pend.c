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
typedef  int uint32_t ;
typedef  scalar_t__ thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  act_set_kperf (scalar_t__) ; 
 scalar_t__ current_thread () ; 
 int kperf_get_thread_flags (scalar_t__) ; 
 int /*<<< orphan*/  kperf_set_thread_flags (scalar_t__,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
kperf_ast_pend(thread_t thread, uint32_t set_flags)
{
	/* can only pend on the current thread */
	if (thread != current_thread()) {
		panic("pending to non-current thread");
	}

	/* get our current bits */
	uint32_t flags = kperf_get_thread_flags(thread);

	/* see if it's already been done or pended */
	if (!(flags & set_flags)) {
		/* set the bit on the thread */
		flags |= set_flags;
		kperf_set_thread_flags(thread, flags);

		/* set the actual AST */
		act_set_kperf(thread);
		return 1;
	}

	return 0;
}