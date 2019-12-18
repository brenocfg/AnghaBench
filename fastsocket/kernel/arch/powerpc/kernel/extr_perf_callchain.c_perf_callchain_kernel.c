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
struct pt_regs {unsigned long link; unsigned long* gpr; unsigned long nip; } ;
struct perf_callchain_entry {int dummy; } ;

/* Variables and functions */
 unsigned long PERF_CONTEXT_KERNEL ; 
 size_t STACK_FRAME_LR_SAVE ; 
 size_t STACK_FRAME_MARKER ; 
 scalar_t__ STACK_FRAME_OVERHEAD ; 
 unsigned long STACK_FRAME_REGS_MARKER ; 
 unsigned long STACK_INT_FRAME_SIZE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry*,unsigned long) ; 
 unsigned long perf_instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  valid_next_sp (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  validate_sp (unsigned long,int /*<<< orphan*/ ,scalar_t__) ; 

void
perf_callchain_kernel(struct perf_callchain_entry *entry, struct pt_regs *regs)
{
	unsigned long sp, next_sp;
	unsigned long next_ip;
	unsigned long lr;
	long level = 0;
	unsigned long *fp;

	lr = regs->link;
	sp = regs->gpr[1];
	perf_callchain_store(entry, perf_instruction_pointer(regs));

	if (!validate_sp(sp, current, STACK_FRAME_OVERHEAD))
		return;

	for (;;) {
		fp = (unsigned long *) sp;
		next_sp = fp[0];

		if (next_sp == sp + STACK_INT_FRAME_SIZE &&
		    fp[STACK_FRAME_MARKER] == STACK_FRAME_REGS_MARKER) {
			/*
			 * This looks like an interrupt frame for an
			 * interrupt that occurred in the kernel
			 */
			regs = (struct pt_regs *)(sp + STACK_FRAME_OVERHEAD);
			next_ip = regs->nip;
			lr = regs->link;
			level = 0;
			perf_callchain_store(entry, PERF_CONTEXT_KERNEL);

		} else {
			if (level == 0)
				next_ip = lr;
			else
				next_ip = fp[STACK_FRAME_LR_SAVE];

			/*
			 * We can't tell which of the first two addresses
			 * we get are valid, but we can filter out the
			 * obviously bogus ones here.  We replace them
			 * with 0 rather than removing them entirely so
			 * that userspace can tell which is which.
			 */
			if ((level == 1 && next_ip == lr) ||
			    (level <= 1 && !kernel_text_address(next_ip)))
				next_ip = 0;

			++level;
		}

		perf_callchain_store(entry, next_ip);
		if (!valid_next_sp(next_sp, sp))
			return;
		sp = next_sp;
	}
}