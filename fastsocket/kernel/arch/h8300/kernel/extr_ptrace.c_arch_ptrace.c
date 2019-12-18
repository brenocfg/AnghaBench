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
struct user {int dummy; } ;
struct task_struct {long exit_code; int /*<<< orphan*/  exit_state; TYPE_1__* mm; } ;
struct TYPE_2__ {unsigned long start_code; unsigned long start_data; unsigned long end_code; unsigned long end_data; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 int /*<<< orphan*/  EXIT_ZOMBIE ; 
 long H8300_REGS_NO ; 
#define  PTRACE_CONT 140 
#define  PTRACE_DETACH 139 
#define  PTRACE_GETREGS 138 
#define  PTRACE_KILL 137 
#define  PTRACE_PEEKDATA 136 
#define  PTRACE_PEEKTEXT 135 
#define  PTRACE_PEEKUSR 134 
#define  PTRACE_POKEDATA 133 
#define  PTRACE_POKETEXT 132 
#define  PTRACE_POKEUSR 131 
#define  PTRACE_SETREGS 130 
#define  PTRACE_SINGLESTEP 129 
#define  PTRACE_SYSCALL 128 
 long PT_ORIG_ER0 ; 
 long SIGKILL ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int generic_ptrace_pokedata (struct task_struct*,long,long) ; 
 int /*<<< orphan*/  get_user (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  h8300_disable_trace (struct task_struct*) ; 
 int /*<<< orphan*/  h8300_enable_trace (struct task_struct*) ; 
 unsigned long h8300_get_reg (struct task_struct*,int) ; 
 int h8300_put_reg (struct task_struct*,int,unsigned long) ; 
 int ptrace_detach (struct task_struct*,long) ; 
 int put_user (unsigned long,unsigned long*) ; 
 int read_long (struct task_struct*,long,unsigned long*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_signal (long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

long arch_ptrace(struct task_struct *child, long request, long addr, long data)
{
	int ret;

	switch (request) {
		case PTRACE_PEEKTEXT: /* read word at location addr. */ 
		case PTRACE_PEEKDATA: {
			unsigned long tmp;

			ret = read_long(child, addr, &tmp);
			if (ret < 0)
				break ;
			ret = put_user(tmp, (unsigned long *) data);
			break ;
		}

	/* read the word at location addr in the USER area. */
		case PTRACE_PEEKUSR: {
			unsigned long tmp = 0;
			
			if ((addr & 3) || addr < 0 || addr >= sizeof(struct user)) {
				ret = -EIO;
				break ;
			}
			
		        ret = 0;  /* Default return condition */
			addr = addr >> 2; /* temporary hack. */

			if (addr < H8300_REGS_NO)
				tmp = h8300_get_reg(child, addr);
			else {
				switch(addr) {
				case 49:
					tmp = child->mm->start_code;
					break ;
				case 50:
					tmp = child->mm->start_data;
					break ;
				case 51:
					tmp = child->mm->end_code;
					break ;
				case 52:
					tmp = child->mm->end_data;
					break ;
				default:
					ret = -EIO;
				}
			}
			if (!ret)
				ret = put_user(tmp,(unsigned long *) data);
			break ;
		}

      /* when I and D space are separate, this will have to be fixed. */
		case PTRACE_POKETEXT: /* write the word at location addr. */
		case PTRACE_POKEDATA:
			ret = generic_ptrace_pokedata(child, addr, data);
			break;

		case PTRACE_POKEUSR: /* write the word at location addr in the USER area */
			if ((addr & 3) || addr < 0 || addr >= sizeof(struct user)) {
				ret = -EIO;
				break ;
			}
			addr = addr >> 2; /* temporary hack. */
			    
			if (addr == PT_ORIG_ER0) {
				ret = -EIO;
				break ;
			}
			if (addr < H8300_REGS_NO) {
				ret = h8300_put_reg(child, addr, data);
				break ;
			}
			ret = -EIO;
			break ;
		case PTRACE_SYSCALL: /* continue and stop at next (return from) syscall */
		case PTRACE_CONT: { /* restart after signal. */
			ret = -EIO;
			if (!valid_signal(data))
				break ;
			if (request == PTRACE_SYSCALL)
				set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
			else
				clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
			child->exit_code = data;
			wake_up_process(child);
			/* make sure the single step bit is not set. */
			h8300_disable_trace(child);
			ret = 0;
		}

/*
 * make the child exit.  Best I can do is send it a sigkill. 
 * perhaps it should be put in the status that it wants to 
 * exit.
 */
		case PTRACE_KILL: {

			ret = 0;
			if (child->exit_state == EXIT_ZOMBIE) /* already dead */
				break;
			child->exit_code = SIGKILL;
			h8300_disable_trace(child);
			wake_up_process(child);
			break;
		}

		case PTRACE_SINGLESTEP: {  /* set the trap flag. */
			ret = -EIO;
			if (!valid_signal(data))
				break;
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
			child->exit_code = data;
			h8300_enable_trace(child);
			wake_up_process(child);
			ret = 0;
			break;
		}

		case PTRACE_DETACH:	/* detach a process that was attached. */
			ret = ptrace_detach(child, data);
			break;

		case PTRACE_GETREGS: { /* Get all gp regs from the child. */
		  	int i;
			unsigned long tmp;
			for (i = 0; i < H8300_REGS_NO; i++) {
			    tmp = h8300_get_reg(child, i);
			    if (put_user(tmp, (unsigned long *) data)) {
				ret = -EFAULT;
				break;
			    }
			    data += sizeof(long);
			}
			ret = 0;
			break;
		}

		case PTRACE_SETREGS: { /* Set all gp regs in the child. */
			int i;
			unsigned long tmp;
			for (i = 0; i < H8300_REGS_NO; i++) {
			    if (get_user(tmp, (unsigned long *) data)) {
				ret = -EFAULT;
				break;
			    }
			    h8300_put_reg(child, i, tmp);
			    data += sizeof(long);
			}
			ret = 0;
			break;
		}

		default:
			ret = -EIO;
			break;
	}
	return ret;
}