#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fpu_state; TYPE_1__* uregs; } ;
struct task_struct {TYPE_2__ thread; } ;
struct fpucontext {int dummy; } ;
struct fpu_state_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  epsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSW_FE ; 
 int /*<<< orphan*/  clear_using_fpu (struct task_struct*) ; 
 scalar_t__ copy_to_user (struct fpucontext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  fpu_save (int /*<<< orphan*/ *) ; 
 struct task_struct* fpu_state_owner ; 
 int /*<<< orphan*/  is_using_fpu (struct task_struct*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

int fpu_setup_sigcontext(struct fpucontext *fpucontext)
{
#ifdef CONFIG_FPU
	struct task_struct *tsk = current;

	if (!is_using_fpu(tsk))
		return 0;

	/* transfer the current FPU state to memory and cause fpu_init() to be
	 * triggered by the next attempted FPU operation by the current
	 * process.
	 */
	preempt_disable();

	if (fpu_state_owner == tsk) {
		fpu_save(&tsk->thread.fpu_state);
		fpu_state_owner->thread.uregs->epsw &= ~EPSW_FE;
		fpu_state_owner = NULL;
	}

	preempt_enable();

	/* we no longer have a valid current FPU state */
	clear_using_fpu(tsk);

	/* transfer the saved FPU state onto the userspace stack */
	if (copy_to_user(fpucontext,
			 &tsk->thread.fpu_state,
			 min(sizeof(struct fpu_state_struct),
			     sizeof(struct fpucontext))))
		return -1;

	return 1;
#else
	return 0;
#endif
}