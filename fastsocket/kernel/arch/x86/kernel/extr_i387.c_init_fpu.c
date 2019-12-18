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
struct TYPE_2__ {int /*<<< orphan*/  xstate; } ;
struct task_struct {TYPE_1__ thread; } ;
struct fpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAVE_HWFP ; 
 struct task_struct* current ; 
 int fpu_alloc (struct fpu*) ; 
 int /*<<< orphan*/  fpu_finit (struct fpu*) ; 
 int /*<<< orphan*/  set_stopped_child_used_math (struct task_struct*) ; 
 scalar_t__ tsk_used_math (struct task_struct*) ; 
 int /*<<< orphan*/  unlazy_fpu (struct task_struct*) ; 

int init_fpu(struct task_struct *tsk)
{
	int ret;

	if (tsk_used_math(tsk)) {
		if (HAVE_HWFP && tsk == current)
			unlazy_fpu(tsk);
		return 0;
	}

	/*
	 * Memory allocation at the first usage of the FPU and other state.
	 */
	ret = fpu_alloc((struct fpu *)&tsk->thread.xstate);
	if (ret)
		return ret;

	fpu_finit((struct fpu *)&tsk->thread.xstate);

	set_stopped_child_used_math(tsk);
	return 0;
}