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
struct arm_saved_state {int* r; } ;

/* Variables and functions */
 struct arm_saved_state* get_user_regs (int /*<<< orphan*/ ) ; 

void
thread_set_parent(
		  thread_t parent,
		  int pid)
{
	struct arm_saved_state *parent_state;

	parent_state = get_user_regs(parent);

	parent_state->r[0] = pid;
	parent_state->r[1] = 0;
}