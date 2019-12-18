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

/* Variables and functions */
 struct arm_saved_state* get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_saved_state_reg (struct arm_saved_state*,int,unsigned long long) ; 

void
thread_set_child(
		 thread_t child,
		 int pid)
{
	struct arm_saved_state *child_state;

	child_state = get_user_regs(child);

	set_saved_state_reg(child_state, 0, pid);
	set_saved_state_reg(child_state, 1, 1ULL);
}