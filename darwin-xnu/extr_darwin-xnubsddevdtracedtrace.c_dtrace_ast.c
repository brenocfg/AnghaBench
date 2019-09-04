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
typedef  int /*<<< orphan*/  dtrace_state_t ;

/* Variables and functions */
 int DTRACE_NCLIENTS ; 
 int atomic_and_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/ * dtrace_state_get (int) ; 
 int /*<<< orphan*/  dtrace_wake_clients ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
dtrace_ast(void)
{
	int i;
	uint32_t clients = atomic_and_32(&dtrace_wake_clients, 0);
	if (clients == 0)
		return;
	/**
	 * We disable preemption here to be sure that we won't get
	 * interrupted by a wakeup to a thread that is higher
	 * priority than us, so that we do issue all wakeups
	 */
	disable_preemption();
	for (i = 0; i < DTRACE_NCLIENTS; i++) {
		if (clients & (1 << i)) {
			dtrace_state_t *state = dtrace_state_get(i);
			if (state) {
				wakeup(state);
			}

		}
	}
	enable_preemption();
}