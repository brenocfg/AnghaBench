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
struct switch_stack {int /*<<< orphan*/  a5; } ;
struct sigcontext {int sc_sr; int sc_formatvec; int sc_d0; int /*<<< orphan*/  sc_usp; int /*<<< orphan*/  sc_pc; int /*<<< orphan*/  sc_a5; int /*<<< orphan*/  sc_a1; int /*<<< orphan*/  sc_a0; int /*<<< orphan*/  sc_d1; } ;
struct pt_regs {int sr; int orig_d0; int format; int vector; int /*<<< orphan*/  pc; int /*<<< orphan*/  a1; int /*<<< orphan*/  a0; int /*<<< orphan*/  d1; } ;
typedef  int /*<<< orphan*/  context ;
struct TYPE_3__ {int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {TYPE_1__ restart_block; } ;

/* Variables and functions */
 scalar_t__ copy_from_user (struct sigcontext*,struct sigcontext*,int) ; 
 TYPE_2__* current_thread_info () ; 
 int /*<<< orphan*/  do_no_restart_syscall ; 
 int restore_fpu_state (struct sigcontext*) ; 
 int /*<<< orphan*/  wrusp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
restore_sigcontext(struct pt_regs *regs, struct sigcontext *usc, void *fp,
		   int *pd0)
{
	int formatvec;
	struct sigcontext context;
	int err = 0;

	/* Always make any pending restarted system calls return -EINTR */
	current_thread_info()->restart_block.fn = do_no_restart_syscall;

	/* get previous context */
	if (copy_from_user(&context, usc, sizeof(context)))
		goto badframe;
	
	/* restore passed registers */
	regs->d1 = context.sc_d1;
	regs->a0 = context.sc_a0;
	regs->a1 = context.sc_a1;
	((struct switch_stack *)regs - 1)->a5 = context.sc_a5;
	regs->sr = (regs->sr & 0xff00) | (context.sc_sr & 0xff);
	regs->pc = context.sc_pc;
	regs->orig_d0 = -1;		/* disable syscall checks */
	wrusp(context.sc_usp);
	formatvec = context.sc_formatvec;
	regs->format = formatvec >> 12;
	regs->vector = formatvec & 0xfff;

#ifdef CONFIG_FPU
	err = restore_fpu_state(&context);
#endif

	*pd0 = context.sc_d0;
	return err;

badframe:
	return 1;
}