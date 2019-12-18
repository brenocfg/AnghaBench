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
struct sh_fpu_soft_struct {int dummy; } ;
struct TYPE_3__ {struct sh_fpu_soft_struct soft; } ;
struct TYPE_4__ {TYPE_1__ fpu; } ;
struct task_struct {TYPE_2__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_USEDFPU ; 
 struct task_struct* current ; 
 int fpu_emulate (unsigned short,struct sh_fpu_soft_struct*,struct pt_regs*) ; 
 int /*<<< orphan*/  fpu_init (struct sh_fpu_soft_struct*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

int do_fpu_inst(unsigned short inst, struct pt_regs *regs)
{
	struct task_struct *tsk = current;
	struct sh_fpu_soft_struct *fpu = &(tsk->thread.fpu.soft);

	if (!test_tsk_thread_flag(tsk, TIF_USEDFPU)) {
		/* initialize once. */
		fpu_init(fpu);
		set_tsk_thread_flag(tsk, TIF_USEDFPU);
	}

	return fpu_emulate(inst, fpu, regs);
}