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
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  dcache_flush_trap (scalar_t__,scalar_t__) ; 
 scalar_t__ get_saved_state_reg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  icache_invalidate_trap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  platform_syscall_kprintf (char*,...) ; 
 int /*<<< orphan*/  set_saved_state_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 int /*<<< orphan*/  thread_get_cthread_self () ; 
 int /*<<< orphan*/  thread_set_cthread_self (scalar_t__) ; 

__attribute__((noreturn))
void
platform_syscall(arm_saved_state_t *state)
{
	uint32_t code;

#define platform_syscall_kprintf(x...) /* kprintf("platform_syscall: " x) */

	code = (uint32_t)get_saved_state_reg(state, 3);
	switch (code) {
	case 0:
		/* I-Cache flush */
		platform_syscall_kprintf("icache flush requested.\n");
		icache_invalidate_trap(get_saved_state_reg(state, 0), get_saved_state_reg(state, 1));
		break;
	case 1:
		/* D-Cache flush */
		platform_syscall_kprintf("dcache flush requested.\n");
		dcache_flush_trap(get_saved_state_reg(state, 0), get_saved_state_reg(state, 1));
		break;
	case 2:
		/* set cthread */
		platform_syscall_kprintf("set cthread self.\n");
		thread_set_cthread_self(get_saved_state_reg(state, 0));
		break;
	case 3:
		/* get cthread */
		platform_syscall_kprintf("get cthread self.\n");
		set_saved_state_reg(state, 0, thread_get_cthread_self());
		break;
	default:
		platform_syscall_kprintf("unknown: %d\n", code);
		break;
	}

	thread_exception_return();
}