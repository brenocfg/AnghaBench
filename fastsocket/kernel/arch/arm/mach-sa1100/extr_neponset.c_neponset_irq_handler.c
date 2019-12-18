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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;int /*<<< orphan*/  (* mask ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NEPONSET_SA1111 ; 
 int /*<<< orphan*/  IRQ_NEPONSET_SMC9196 ; 
 int /*<<< orphan*/  IRQ_NEPONSET_USAR ; 
 unsigned int IRR ; 
 unsigned int IRR_ETHERNET ; 
 unsigned int IRR_SA1111 ; 
 unsigned int IRR_USAR ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 
 int /*<<< orphan*/  stub4 (unsigned int) ; 

__attribute__((used)) static void
neponset_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	unsigned int irr;

	while (1) {
		/*
		 * Acknowledge the parent IRQ.
		 */
		desc->chip->ack(irq);

		/*
		 * Read the interrupt reason register.  Let's have all
		 * active IRQ bits high.  Note: there is a typo in the
		 * Neponset user's guide for the SA1111 IRR level.
		 */
		irr = IRR ^ (IRR_ETHERNET | IRR_USAR);

		if ((irr & (IRR_ETHERNET | IRR_USAR | IRR_SA1111)) == 0)
			break;

		/*
		 * Since there is no individual mask, we have to
		 * mask the parent IRQ.  This is safe, since we'll
		 * recheck the register for any pending IRQs.
		 */
		if (irr & (IRR_ETHERNET | IRR_USAR)) {
			desc->chip->mask(irq);

			/*
			 * Ack the interrupt now to prevent re-entering
			 * this neponset handler.  Again, this is safe
			 * since we'll check the IRR register prior to
			 * leaving.
			 */
			desc->chip->ack(irq);

			if (irr & IRR_ETHERNET) {
				generic_handle_irq(IRQ_NEPONSET_SMC9196);
			}

			if (irr & IRR_USAR) {
				generic_handle_irq(IRQ_NEPONSET_USAR);
			}

			desc->chip->unmask(irq);
		}

		if (irr & IRR_SA1111) {
			generic_handle_irq(IRQ_NEPONSET_SA1111);
		}
	}
}