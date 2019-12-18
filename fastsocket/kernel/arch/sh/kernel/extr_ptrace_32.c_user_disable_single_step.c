#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ubc_pc; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int ubc_usercnt ; 

void user_disable_single_step(struct task_struct *child)
{
	clear_tsk_thread_flag(child, TIF_SINGLESTEP);

	/*
	 * Ensure the UBC is not programmed at the next context switch.
	 *
	 * Normally this is not needed but there are sequences such as
	 * singlestep, signal delivery, and continue that leave the
	 * ubc_pc non-zero leading to spurious SIGTRAPs.
	 */
	if (child->thread.ubc_pc != 0) {
		ubc_usercnt -= 1;
		child->thread.ubc_pc = 0;
	}
}