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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIRST_IRQ ; 
 int IGNORE_MASK ; 
 int NBR_REGS ; 
 int REG_RD_INT_VECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WR_INT_VECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ TIMER0_INTR_VECT ; 
 int TIMER_MASK ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__,struct pt_regs*) ; 
 int /*<<< orphan*/  intr_vect ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/ * irq_regs ; 
 int /*<<< orphan*/  r_masked_vect ; 
 int /*<<< orphan*/  rw_mask ; 
 int smp_processor_id () ; 

void
crisv32_do_multiple(struct pt_regs* regs)
{
	int cpu;
	int mask;
	int masked[NBR_REGS];
	int bit;
	int i;

	cpu = smp_processor_id();

	/* An extra irq_enter here to prevent softIRQs to run after
         * each do_IRQ. This will decrease the interrupt latency.
	 */
	irq_enter();

	for (i = 0; i < NBR_REGS; i++) {
		/* Get which IRQs that happend. */
		masked[i] = REG_RD_INT_VECT(intr_vect, irq_regs[cpu],
			r_masked_vect, i);

		/* Calculate new IRQ mask with these IRQs disabled. */
		mask = REG_RD_INT_VECT(intr_vect, irq_regs[cpu], rw_mask, i);
		mask &= ~masked[i];

	/* Timer IRQ is never masked */
#ifdef TIMER_VECT1
		if ((i == 1) && (masked[0] & TIMER_MASK))
			mask |= TIMER_MASK;
#else
		if ((i == 0) && (masked[0] & TIMER_MASK))
			mask |= TIMER_MASK;
#endif
		/* Block all the IRQs */
		REG_WR_INT_VECT(intr_vect, irq_regs[cpu], rw_mask, i, mask);

	/* Check for timer IRQ and handle it special. */
#ifdef TIMER_VECT1
		if ((i == 1) && (masked[i] & TIMER_MASK)) {
			masked[i] &= ~TIMER_MASK;
			do_IRQ(TIMER0_INTR_VECT, regs);
		}
#else
		if ((i == 0) && (masked[i] & TIMER_MASK)) {
			 masked[i] &= ~TIMER_MASK;
			 do_IRQ(TIMER0_INTR_VECT, regs);
		}
#endif
	}

#ifdef IGNORE_MASK
	/* Remove IRQs that can't be handled as multiple. */
	masked[0] &= ~IGNORE_MASK;
#endif

	/* Handle the rest of the IRQs. */
	for (i = 0; i < NBR_REGS; i++) {
		for (bit = 0; bit < 32; bit++) {
			if (masked[i] & (1 << bit))
				do_IRQ(bit + FIRST_IRQ + i*32, regs);
		}
	}

	/* Unblock all the IRQs. */
	for (i = 0; i < NBR_REGS; i++) {
		mask = REG_RD_INT_VECT(intr_vect, irq_regs[cpu], rw_mask, i);
		mask |= masked[i];
		REG_WR_INT_VECT(intr_vect, irq_regs[cpu], rw_mask, i, mask);
	}

	/* This irq_exit() will trigger the soft IRQs. */
	irq_exit();
}