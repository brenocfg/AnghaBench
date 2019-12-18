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
typedef  int /*<<< orphan*/  tmp ;
struct task_struct {long exit_code; int /*<<< orphan*/  exit_state; } ;
struct TYPE_2__ {int bpt_nsaved; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_MEM ; 
 long EIO ; 
 int /*<<< orphan*/  EXIT_ZOMBIE ; 
#define  PTRACE_CONT 137 
#define  PTRACE_KILL 136 
#define  PTRACE_PEEKDATA 135 
#define  PTRACE_PEEKTEXT 134 
#define  PTRACE_PEEKUSR 133 
#define  PTRACE_POKEDATA 132 
#define  PTRACE_POKETEXT 131 
#define  PTRACE_POKEUSR 130 
#define  PTRACE_SINGLESTEP 129 
#define  PTRACE_SYSCALL 128 
 long SIGKILL ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 size_t access_process_vm (struct task_struct*,long,unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_successful_syscall_return () ; 
 long generic_ptrace_pokedata (struct task_struct*,long,long) ; 
 long get_reg (struct task_struct*,long) ; 
 int /*<<< orphan*/  ptrace_cancel_bpt (struct task_struct*) ; 
 long ptrace_request (struct task_struct*,long,long,long) ; 
 long put_reg (struct task_struct*,long,long) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  valid_signal (long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

long arch_ptrace(struct task_struct *child, long request, long addr, long data)
{
	unsigned long tmp;
	size_t copied;
	long ret;

	switch (request) {
	/* When I and D space are separate, these will need to be fixed.  */
	case PTRACE_PEEKTEXT: /* read word at location addr. */
	case PTRACE_PEEKDATA:
		copied = access_process_vm(child, addr, &tmp, sizeof(tmp), 0);
		ret = -EIO;
		if (copied != sizeof(tmp))
			break;
		
		force_successful_syscall_return();
		ret = tmp;
		break;

	/* Read register number ADDR. */
	case PTRACE_PEEKUSR:
		force_successful_syscall_return();
		ret = get_reg(child, addr);
		DBG(DBG_MEM, ("peek $%ld->%#lx\n", addr, ret));
		break;

	/* When I and D space are separate, this will have to be fixed.  */
	case PTRACE_POKETEXT: /* write the word at location addr. */
	case PTRACE_POKEDATA:
		ret = generic_ptrace_pokedata(child, addr, data);
		break;

	case PTRACE_POKEUSR: /* write the specified register */
		DBG(DBG_MEM, ("poke $%ld<-%#lx\n", addr, data));
		ret = put_reg(child, addr, data);
		break;

	case PTRACE_SYSCALL:
		/* continue and stop at next (return from) syscall */
	case PTRACE_CONT:    /* restart after signal. */
		ret = -EIO;
		if (!valid_signal(data))
			break;
		if (request == PTRACE_SYSCALL)
			set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		else
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		child->exit_code = data;
		/* make sure single-step breakpoint is gone. */
		ptrace_cancel_bpt(child);
		wake_up_process(child);
		ret = 0;
		break;

	/*
	 * Make the child exit.  Best I can do is send it a sigkill.
	 * perhaps it should be put in the status that it wants to
	 * exit.
	 */
	case PTRACE_KILL:
		ret = 0;
		if (child->exit_state == EXIT_ZOMBIE)
			break;
		child->exit_code = SIGKILL;
		/* make sure single-step breakpoint is gone. */
		ptrace_cancel_bpt(child);
		wake_up_process(child);
		break;

	case PTRACE_SINGLESTEP:  /* execute single instruction. */
		ret = -EIO;
		if (!valid_signal(data))
			break;
		/* Mark single stepping.  */
		task_thread_info(child)->bpt_nsaved = -1;
		clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		child->exit_code = data;
		wake_up_process(child);
		/* give it a chance to run. */
		ret = 0;
		break;

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
	return ret;
}