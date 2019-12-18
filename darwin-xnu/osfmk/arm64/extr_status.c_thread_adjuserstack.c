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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct arm_saved_state {int dummy; } ;

/* Variables and functions */
 int get_saved_state_sp (struct arm_saved_state*) ; 
 struct arm_saved_state* get_user_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_saved_state_sp (struct arm_saved_state*,int) ; 

uint64_t
thread_adjuserstack(thread_t thread, int adjust)
{
	struct arm_saved_state *sv;
	uint64_t sp;

	sv = get_user_regs(thread);

	sp = get_saved_state_sp(sv);
	sp += adjust;
	set_saved_state_sp(sv, sp);;

	return sp;
}