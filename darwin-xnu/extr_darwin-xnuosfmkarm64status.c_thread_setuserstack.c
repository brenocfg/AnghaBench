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
struct arm_saved_state {int dummy; } ;
typedef  int /*<<< orphan*/  mach_vm_address_t ;

/* Variables and functions */
 struct arm_saved_state* get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_saved_state_sp (struct arm_saved_state*,int /*<<< orphan*/ ) ; 

void
thread_setuserstack(thread_t thread, mach_vm_address_t user_stack)
{
	struct arm_saved_state *sv;

	sv = get_user_regs(thread);

	set_saved_state_sp(sv, user_stack);

	return;
}