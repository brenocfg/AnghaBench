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
 unsigned int IO_MASK (unsigned int*,int /*<<< orphan*/ ) ; 
 unsigned int IO_STATE (unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* R_VECT_MASK_CLR ; 
 unsigned int* R_VECT_MASK_RD ; 
 unsigned int* R_VECT_MASK_SET ; 
 int /*<<< orphan*/  active ; 
 int /*<<< orphan*/  dma0 ; 
 int /*<<< orphan*/  dma1 ; 
 int /*<<< orphan*/  do_IRQ (int,struct pt_regs*) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  timer0 ; 

void do_multiple_IRQ(struct pt_regs* regs)
{
	int bit;
	unsigned masked;
	unsigned mask;
	unsigned ethmask = 0;

	/* Get interrupts to mask and handle */
	mask = masked = *R_VECT_MASK_RD;

	/* Never mask timer IRQ */
	mask &= ~(IO_MASK(R_VECT_MASK_RD, timer0));

	/*
	 * If either ethernet interrupt (rx or tx) is active then block
	 * the other one too. Unblock afterwards also.
	 */
	if (mask &
	    (IO_STATE(R_VECT_MASK_RD, dma0, active) |
	     IO_STATE(R_VECT_MASK_RD, dma1, active))) {
		ethmask = (IO_MASK(R_VECT_MASK_RD, dma0) |
			   IO_MASK(R_VECT_MASK_RD, dma1));
	}

	/* Block them */
	*R_VECT_MASK_CLR = (mask | ethmask);

	/* An extra irq_enter here to prevent softIRQs to run after
	 * each do_IRQ. This will decrease the interrupt latency.
	 */
	irq_enter();

	/* Handle all IRQs */
	for (bit = 2; bit < 32; bit++) {
		if (masked & (1 << bit)) {
			do_IRQ(bit, regs);
		}
	}

	/* This irq_exit() will trigger the soft IRQs. */
	irq_exit();

	/* Unblock the IRQs again */
	*R_VECT_MASK_SET = (masked | ethmask);
}