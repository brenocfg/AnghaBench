#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt_regs {int pc; unsigned long* regs; } ;

/* Variables and functions */
 unsigned long __MEMORY_START ; 
 scalar_t__ lookup_prev_stack_frame (unsigned long,unsigned long,unsigned long*,unsigned long*,struct pt_regs*) ; 
 int /*<<< orphan*/  print_symbol (char*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  ret_from_exception ; 
 int /*<<< orphan*/  ret_from_irq ; 
 int /*<<< orphan*/  ret_from_syscall ; 
 int /*<<< orphan*/  syscall_ret ; 
 int /*<<< orphan*/  unwind_nested (unsigned long,unsigned long) ; 

__attribute__((used)) static void sh64_unwind_inner(struct pt_regs *regs)
{
	unsigned long pc, fp;
	int ofs = 0;
	int first_pass;

	pc = regs->pc & ~1;
	fp = regs->regs[14];

	first_pass = 1;
	for (;;) {
		int cond;
		unsigned long next_fp, next_pc;

		if (pc == ((unsigned long) &syscall_ret & ~1)) {
			printk("SYSCALL\n");
			unwind_nested(pc,fp);
			return;
		}

		if (pc == ((unsigned long) &ret_from_syscall & ~1)) {
			printk("SYSCALL (PREEMPTED)\n");
			unwind_nested(pc,fp);
			return;
		}

		/* In this case, the PC is discovered by lookup_prev_stack_frame but
		   it has 4 taken off it to look like the 'caller' */
		if (pc == ((unsigned long) &ret_from_exception & ~1)) {
			printk("EXCEPTION\n");
			unwind_nested(pc,fp);
			return;
		}

		if (pc == ((unsigned long) &ret_from_irq & ~1)) {
			printk("IRQ\n");
			unwind_nested(pc,fp);
			return;
		}

		cond = ((pc >= __MEMORY_START) && (fp >= __MEMORY_START) &&
			((pc & 3) == 0) && ((fp & 7) == 0));

		pc -= ofs;

		printk("[<%08lx>] ", pc);
		print_symbol("%s\n", pc);

		if (first_pass) {
			/* If the innermost frame is a leaf function, it's
			 * possible that r18 is never saved out to the stack.
			 */
			next_pc = regs->regs[18];
		} else {
			next_pc = 0;
		}

		if (lookup_prev_stack_frame(fp, pc, &next_fp, &next_pc, regs) == 0) {
			ofs = sizeof(unsigned long);
			pc = next_pc & ~1;
			fp = next_fp;
		} else {
			printk("Unable to lookup previous stack frame\n");
			break;
		}
		first_pass = 0;
	}

	printk("\n");

}