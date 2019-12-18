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
typedef  int /*<<< orphan*/  val ;
struct task_struct {long exit_code; int /*<<< orphan*/  exit_state; TYPE_1__* mm; } ;
typedef  unsigned long microblaze_reg_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {unsigned long start_code; unsigned long start_data; unsigned long end_code; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXIT_ZOMBIE ; 
#define  PTRACE_CONT 138 
#define  PTRACE_DETACH 137 
#define  PTRACE_KILL 136 
#define  PTRACE_PEEKDATA 135 
#define  PTRACE_PEEKTEXT 134 
#define  PTRACE_PEEKUSR 133 
#define  PTRACE_POKEDATA 132 
#define  PTRACE_POKETEXT 131 
#define  PTRACE_POKEUSR 130 
#define  PTRACE_SINGLESTEP 129 
#define  PTRACE_SYSCALL 128 
 long PT_DATA_ADDR ; 
 long PT_SIZE ; 
 long PT_TEXT_ADDR ; 
 long PT_TEXT_LEN ; 
 long SIGKILL ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int access_process_vm (struct task_struct*,long,...) ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int ptrace_detach (struct task_struct*,long) ; 
 int put_user (unsigned long,unsigned long*) ; 
 unsigned long* reg_save_addr (long,struct task_struct*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_signal (long) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

long arch_ptrace(struct task_struct *child, long request, long addr, long data)
{
	int rval;
	unsigned long val = 0;
	unsigned long copied;

	switch (request) {
	case PTRACE_PEEKTEXT: /* read word at location addr. */
	case PTRACE_PEEKDATA:
		pr_debug("PEEKTEXT/PEEKDATA at %08lX\n", addr);
		copied = access_process_vm(child, addr, &val, sizeof(val), 0);
		rval = -EIO;
		if (copied != sizeof(val))
			break;
		rval = put_user(val, (unsigned long *)data);
		break;

	case PTRACE_POKETEXT: /* write the word at location addr. */
	case PTRACE_POKEDATA:
		pr_debug("POKETEXT/POKEDATA to %08lX\n", addr);
		rval = 0;
		if (access_process_vm(child, addr, &data, sizeof(data), 1)
		    == sizeof(data))
			break;
		rval = -EIO;
		break;

	/* Read/write the word at location ADDR in the registers. */
	case PTRACE_PEEKUSR:
	case PTRACE_POKEUSR:
		pr_debug("PEEKUSR/POKEUSR : 0x%08lx\n", addr);
		rval = 0;
		if (addr >= PT_SIZE && request == PTRACE_PEEKUSR) {
			/*
			 * Special requests that don't actually correspond
			 * to offsets in struct pt_regs.
			 */
			if (addr == PT_TEXT_ADDR) {
				val = child->mm->start_code;
			} else if (addr == PT_DATA_ADDR) {
				val = child->mm->start_data;
			} else if (addr == PT_TEXT_LEN) {
				val = child->mm->end_code
					- child->mm->start_code;
			} else {
				rval = -EIO;
			}
		} else if (addr >= 0 && addr < PT_SIZE && (addr & 0x3) == 0) {
			microblaze_reg_t *reg_addr = reg_save_addr(addr, child);
			if (request == PTRACE_PEEKUSR)
				val = *reg_addr;
			else
				*reg_addr = data;
		} else
			rval = -EIO;

		if (rval == 0 && request == PTRACE_PEEKUSR)
			rval = put_user(val, (unsigned long *)data);
		break;
	/* Continue and stop at next (return from) syscall */
	case PTRACE_SYSCALL:
		pr_debug("PTRACE_SYSCALL\n");
	case PTRACE_SINGLESTEP:
		pr_debug("PTRACE_SINGLESTEP\n");
	/* Restart after a signal.  */
	case PTRACE_CONT:
		pr_debug("PTRACE_CONT\n");
		rval = -EIO;
		if (!valid_signal(data))
			break;

		if (request == PTRACE_SYSCALL)
			set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		else
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);

		child->exit_code = data;
		pr_debug("wakeup_process\n");
		wake_up_process(child);
		rval = 0;
		break;

	/*
	 * make the child exit.  Best I can do is send it a sigkill.
	 * perhaps it should be put in the status that it wants to
	 * exit.
	 */
	case PTRACE_KILL:
		pr_debug("PTRACE_KILL\n");
		rval = 0;
		if (child->exit_state == EXIT_ZOMBIE)	/* already dead */
			break;
		child->exit_code = SIGKILL;
		wake_up_process(child);
		break;

	case PTRACE_DETACH: /* detach a process that was attached. */
		pr_debug("PTRACE_DETACH\n");
		rval = ptrace_detach(child, data);
		break;
	default:
		/* rval = ptrace_request(child, request, addr, data); noMMU */
		rval = -EIO;
	}
	return rval;
}