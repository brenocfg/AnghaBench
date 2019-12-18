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
struct TYPE_2__ {int preempt_count; int /*<<< orphan*/  previous_sp; int /*<<< orphan*/  task; } ;
union irq_ctx {TYPE_1__ tinfo; } ;
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int SOFTIRQ_MASK ; 
 int /*<<< orphan*/  current_stack_pointer ; 
 scalar_t__ current_thread_info () ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 union irq_ctx** hardirq_ctx ; 
 unsigned int irq_demux (unsigned int) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 size_t smp_processor_id () ; 

int do_IRQ(unsigned int irq, struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);
#ifdef CONFIG_IRQSTACKS
	union irq_ctx *curctx, *irqctx;
#endif

	irq_enter();
	irq = irq_demux(irq);

#ifdef CONFIG_IRQSTACKS
	curctx = (union irq_ctx *)current_thread_info();
	irqctx = hardirq_ctx[smp_processor_id()];

	/*
	 * this is where we switch to the IRQ stack. However, if we are
	 * already using the IRQ stack (because we interrupted a hardirq
	 * handler) we can't do that and just have to keep using the
	 * current stack (which is the irq stack already after all)
	 */
	if (curctx != irqctx) {
		u32 *isp;

		isp = (u32 *)((char *)irqctx + sizeof(*irqctx));
		irqctx->tinfo.task = curctx->tinfo.task;
		irqctx->tinfo.previous_sp = current_stack_pointer;

		/*
		 * Copy the softirq bits in preempt_count so that the
		 * softirq checks work in the hardirq context.
		 */
		irqctx->tinfo.preempt_count =
			(irqctx->tinfo.preempt_count & ~SOFTIRQ_MASK) |
			(curctx->tinfo.preempt_count & SOFTIRQ_MASK);

		__asm__ __volatile__ (
			"mov	%0, r4		\n"
			"mov	r15, r8		\n"
			"jsr	@%1		\n"
			/* swith to the irq stack */
			" mov	%2, r15		\n"
			/* restore the stack (ring zero) */
			"mov	r8, r15		\n"
			: /* no outputs */
			: "r" (irq), "r" (generic_handle_irq), "r" (isp)
			: "memory", "r0", "r1", "r2", "r3", "r4",
			  "r5", "r6", "r7", "r8", "t", "pr"
		);
	} else
#endif
		generic_handle_irq(irq);

	irq_exit();

	set_irq_regs(old_regs);
	return 1;
}