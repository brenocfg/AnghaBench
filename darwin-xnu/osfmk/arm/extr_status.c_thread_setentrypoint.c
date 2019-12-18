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
typedef  int /*<<< orphan*/  thread_t ;
struct arm_saved_state {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;

/* Variables and functions */
 struct arm_saved_state* get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_setentrypoint_kprintf (char*,int /*<<< orphan*/ ) ; 

void
thread_setentrypoint(thread_t thread, mach_vm_offset_t entry)
{
	struct arm_saved_state *sv;

#define thread_setentrypoint_kprintf(x...)	/* kprintf("thread_setentrypoi
						 * nt: " x) */

	sv = get_user_regs(thread);

	sv->pc = entry;

	thread_setentrypoint_kprintf("entry %x\n", sv->pc);

	return;
}