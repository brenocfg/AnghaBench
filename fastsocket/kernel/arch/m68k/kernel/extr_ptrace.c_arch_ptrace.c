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
struct user_m68kfp_struct {int dummy; } ;
struct TYPE_2__ {unsigned long* fp; } ;
struct task_struct {long exit_code; TYPE_1__ thread; int /*<<< orphan*/  exit_state; } ;

/* Variables and functions */
 int EFAULT ; 
 long EIO ; 
 int /*<<< orphan*/  EXIT_ZOMBIE ; 
 int /*<<< orphan*/  FPU_IS_EMU ; 
#define  PTRACE_CONT 141 
#define  PTRACE_GETFPREGS 140 
#define  PTRACE_GETREGS 139 
#define  PTRACE_KILL 138 
#define  PTRACE_PEEKDATA 137 
#define  PTRACE_PEEKTEXT 136 
#define  PTRACE_PEEKUSR 135 
#define  PTRACE_POKEDATA 134 
#define  PTRACE_POKETEXT 133 
#define  PTRACE_POKEUSR 132 
#define  PTRACE_SETFPREGS 131 
#define  PTRACE_SETREGS 130 
#define  PTRACE_SINGLESTEP 129 
#define  PTRACE_SYSCALL 128 
 long PT_SR ; 
 long SIGKILL ; 
 long SR_MASK ; 
 int /*<<< orphan*/  TIF_DELAYED_TRACE ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int TRACE_BITS ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (long**,void*,int) ; 
 int /*<<< orphan*/  copy_to_user (void*,long**,int) ; 
 int generic_ptrace_peekdata (struct task_struct*,long,long) ; 
 int generic_ptrace_pokedata (struct task_struct*,long,long) ; 
 long get_reg (struct task_struct*,long) ; 
 int get_user (unsigned long,unsigned long*) ; 
 int ptrace_request (struct task_struct*,long,long,long) ; 
 int /*<<< orphan*/  put_reg (struct task_struct*,int,unsigned long) ; 
 int put_user (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  singlestep_disable (struct task_struct*) ; 
 int /*<<< orphan*/  valid_signal (long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

long arch_ptrace(struct task_struct *child, long request, long addr, long data)
{
	unsigned long tmp;
	int i, ret = 0;

	switch (request) {
	/* when I and D space are separate, these will need to be fixed. */
	case PTRACE_PEEKTEXT:	/* read word at location addr. */
	case PTRACE_PEEKDATA:
		ret = generic_ptrace_peekdata(child, addr, data);
		break;

	/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR:
		if (addr & 3)
			goto out_eio;
		addr >>= 2;	/* temporary hack. */

		if (addr >= 0 && addr < 19) {
			tmp = get_reg(child, addr);
			if (addr == PT_SR)
				tmp >>= 16;
		} else if (addr >= 21 && addr < 49) {
			tmp = child->thread.fp[addr - 21];
			/* Convert internal fpu reg representation
			 * into long double format
			 */
			if (FPU_IS_EMU && (addr < 45) && !(addr % 3))
				tmp = ((tmp & 0xffff0000) << 15) |
				      ((tmp & 0x0000ffff) << 16);
		} else
			break;
		ret = put_user(tmp, (unsigned long *)data);
		break;

	/* when I and D space are separate, this will have to be fixed. */
	case PTRACE_POKETEXT:	/* write the word at location addr. */
	case PTRACE_POKEDATA:
		ret = generic_ptrace_pokedata(child, addr, data);
		break;

	case PTRACE_POKEUSR:	/* write the word at location addr in the USER area */
		if (addr & 3)
			goto out_eio;
		addr >>= 2;	/* temporary hack. */

		if (addr == PT_SR) {
			data &= SR_MASK;
			data <<= 16;
			data |= get_reg(child, PT_SR) & ~(SR_MASK << 16);
		} else if (addr >= 0 && addr < 19) {
			if (put_reg(child, addr, data))
				goto out_eio;
		} else if (addr >= 21 && addr < 48) {
			/* Convert long double format
			 * into internal fpu reg representation
			 */
			if (FPU_IS_EMU && (addr < 45) && !(addr % 3)) {
				data = (unsigned long)data << 15;
				data = (data & 0xffff0000) |
				       ((data & 0x0000ffff) >> 1);
			}
			child->thread.fp[addr - 21] = data;
		} else
			goto out_eio;
		break;

	case PTRACE_SYSCALL:	/* continue and stop at next (return from) syscall */
	case PTRACE_CONT:	/* restart after signal. */
		if (!valid_signal(data))
			goto out_eio;

		if (request == PTRACE_SYSCALL)
			set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		else
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		child->exit_code = data;
		singlestep_disable(child);
		wake_up_process(child);
		break;

	/*
	 * make the child exit.  Best I can do is send it a sigkill.
	 * perhaps it should be put in the status that it wants to
	 * exit.
	 */
	case PTRACE_KILL:
		if (child->exit_state == EXIT_ZOMBIE) /* already dead */
			break;
		child->exit_code = SIGKILL;
		singlestep_disable(child);
		wake_up_process(child);
		break;

	case PTRACE_SINGLESTEP:	/* set the trap flag. */
		if (!valid_signal(data))
			goto out_eio;

		clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		tmp = get_reg(child, PT_SR) | (TRACE_BITS << 16);
		put_reg(child, PT_SR, tmp);
		set_tsk_thread_flag(child, TIF_DELAYED_TRACE);

		child->exit_code = data;
		/* give it a chance to run. */
		wake_up_process(child);
		break;

	case PTRACE_GETREGS:	/* Get all gp regs from the child. */
		for (i = 0; i < 19; i++) {
			tmp = get_reg(child, i);
			if (i == PT_SR)
				tmp >>= 16;
			ret = put_user(tmp, (unsigned long *)data);
			if (ret)
				break;
			data += sizeof(long);
		}
		break;

	case PTRACE_SETREGS:	/* Set all gp regs in the child. */
		for (i = 0; i < 19; i++) {
			ret = get_user(tmp, (unsigned long *)data);
			if (ret)
				break;
			if (i == PT_SR) {
				tmp &= SR_MASK;
				tmp <<= 16;
				tmp |= get_reg(child, PT_SR) & ~(SR_MASK << 16);
			}
			put_reg(child, i, tmp);
			data += sizeof(long);
		}
		break;

	case PTRACE_GETFPREGS:	/* Get the child FPU state. */
		if (copy_to_user((void *)data, &child->thread.fp,
				 sizeof(struct user_m68kfp_struct)))
			ret = -EFAULT;
		break;

	case PTRACE_SETFPREGS:	/* Set the child FPU state. */
		if (copy_from_user(&child->thread.fp, (void *)data,
				   sizeof(struct user_m68kfp_struct)))
			ret = -EFAULT;
		break;

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}

	return ret;
out_eio:
	return -EIO;
}