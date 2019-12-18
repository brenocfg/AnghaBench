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
struct TYPE_2__ {int /*<<< orphan*/  fpu_state; } ;
struct task_struct {TYPE_1__ thread; } ;
struct fpucontext {int dummy; } ;
struct fpu_state_struct {int dummy; } ;

/* Variables and functions */
 int copy_from_user (int /*<<< orphan*/ *,struct fpucontext*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  set_using_fpu (struct task_struct*) ; 

int fpu_restore_sigcontext(struct fpucontext *fpucontext)
{
	struct task_struct *tsk = current;
	int ret;

	/* load up the old FPU state */
	ret = copy_from_user(&tsk->thread.fpu_state,
			     fpucontext,
			     min(sizeof(struct fpu_state_struct),
				 sizeof(struct fpucontext)));
	if (!ret)
		set_using_fpu(tsk);

	return ret;
}