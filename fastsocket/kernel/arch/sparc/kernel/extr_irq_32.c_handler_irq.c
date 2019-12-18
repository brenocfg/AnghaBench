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
struct pt_regs {int dummy; } ;
struct irqaction {struct irqaction* next; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  (* handler ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * irqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; struct irqaction* action; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPARC_IRQ_INPROGRESS ; 
 int /*<<< orphan*/  disable_pil_irq (int) ; 
 int /*<<< orphan*/  enable_pil_irq (int) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 TYPE_2__ kstat_cpu (int) ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int smp_processor_id () ; 
 scalar_t__ sparc_cpu_model ; 
 TYPE_1__* sparc_irq ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sun4m ; 
 int /*<<< orphan*/  unexpected_irq (int,int /*<<< orphan*/ *,struct pt_regs*) ; 

void handler_irq(int irq, struct pt_regs * regs)
{
	struct pt_regs *old_regs;
	struct irqaction * action;
	int cpu = smp_processor_id();
#ifdef CONFIG_SMP
	extern void smp4m_irq_rotate(int cpu);
#endif

	old_regs = set_irq_regs(regs);
	irq_enter();
	disable_pil_irq(irq);
#ifdef CONFIG_SMP
	/* Only rotate on lower priority IRQs (scsi, ethernet, etc.). */
	if((sparc_cpu_model==sun4m) && (irq < 10))
		smp4m_irq_rotate(cpu);
#endif
	action = sparc_irq[irq].action;
	sparc_irq[irq].flags |= SPARC_IRQ_INPROGRESS;
	kstat_cpu(cpu).irqs[irq]++;
	do {
		if (!action || !action->handler)
			unexpected_irq(irq, NULL, regs);
		action->handler(irq, action->dev_id);
		action = action->next;
	} while (action);
	sparc_irq[irq].flags &= ~SPARC_IRQ_INPROGRESS;
	enable_pil_irq(irq);
	irq_exit();
	set_irq_regs(old_regs);
}