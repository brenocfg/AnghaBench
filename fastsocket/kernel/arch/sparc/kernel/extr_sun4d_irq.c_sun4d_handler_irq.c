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
struct sbus_action {struct irqaction* action; } ;
struct pt_regs {int dummy; } ;
struct irqaction {struct irqaction* next; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  (* handler ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBI2DEVID (int) ; 
 unsigned int acquire_sbi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bw_clear_intr_mask (int,int) ; 
 int bw_get_intr_mask (int) ; 
 int /*<<< orphan*/  cc_get_ipen () ; 
 int /*<<< orphan*/  cc_set_iclr (int) ; 
 struct irqaction** irq_action ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 TYPE_1__ kstat_cpu (int) ; 
 int* pil_to_sbus ; 
 int /*<<< orphan*/  release_sbi (int /*<<< orphan*/ ,unsigned int) ; 
 struct sbus_action* sbus_actions ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unexpected_irq (int,int /*<<< orphan*/ *,struct pt_regs*) ; 

void sun4d_handler_irq(int irq, struct pt_regs * regs)
{
	struct pt_regs *old_regs;
	struct irqaction * action;
	int cpu = smp_processor_id();
	/* SBUS IRQ level (1 - 7) */
	int sbusl = pil_to_sbus[irq];
	
	/* FIXME: Is this necessary?? */
	cc_get_ipen();
	
	cc_set_iclr(1 << irq);
	
	old_regs = set_irq_regs(regs);
	irq_enter();
	kstat_cpu(cpu).irqs[irq]++;
	if (!sbusl) {
		action = *(irq + irq_action);
		if (!action)
			unexpected_irq(irq, NULL, regs);
		do {
			action->handler(irq, action->dev_id);
			action = action->next;
		} while (action);
	} else {
		int bus_mask = bw_get_intr_mask(sbusl) & 0x3ffff;
		int sbino;
		struct sbus_action *actionp;
		unsigned mask, slot;
		int sbil = (sbusl << 2);
		
		bw_clear_intr_mask(sbusl, bus_mask);
		
		/* Loop for each pending SBI */
		for (sbino = 0; bus_mask; sbino++, bus_mask >>= 1)
			if (bus_mask & 1) {
				mask = acquire_sbi(SBI2DEVID(sbino), 0xf << sbil);
				mask &= (0xf << sbil);
				actionp = sbus_actions + (sbino << 5) + (sbil);
				/* Loop for each pending SBI slot */
				for (slot = (1 << sbil); mask; slot <<= 1, actionp++)
					if (mask & slot) {
						mask &= ~slot;
						action = actionp->action;
						
						if (!action)
							unexpected_irq(irq, NULL, regs);
						do {
							action->handler(irq, action->dev_id);
							action = action->next;
						} while (action);
						release_sbi(SBI2DEVID(sbino), slot);
					}
			}
	}
	irq_exit();
	set_irq_regs(old_regs);
}