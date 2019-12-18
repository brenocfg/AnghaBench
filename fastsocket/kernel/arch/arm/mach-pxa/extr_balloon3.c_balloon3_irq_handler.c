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
struct TYPE_2__ {int /*<<< orphan*/  (* ack ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BALLOON3_AUX_NIRQ ; 
 int /*<<< orphan*/  BALLOON3_INT_CONTROL_REG ; 
 unsigned int BALLOON3_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int __ffs (unsigned long) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long balloon3_irq_enabled ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balloon3_irq_handler(unsigned int irq, struct irq_desc *desc)
{
	unsigned long pending = __raw_readl(BALLOON3_INT_CONTROL_REG) &
					balloon3_irq_enabled;

	do {
		/* clear useless edge notification */
		if (desc->chip->ack)
			desc->chip->ack(BALLOON3_AUX_NIRQ);
		while (pending) {
			irq = BALLOON3_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);
			pending &= pending - 1;
		}
		pending = __raw_readl(BALLOON3_INT_CONTROL_REG) &
				balloon3_irq_enabled;
	} while (pending);
}