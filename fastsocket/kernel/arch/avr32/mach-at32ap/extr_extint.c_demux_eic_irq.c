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
struct irq_desc {struct eic* handler_data; } ;
struct eic {scalar_t__ first_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  ISR ; 
 unsigned long eic_readl (struct eic*,int /*<<< orphan*/ ) ; 
 int fls (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 

__attribute__((used)) static void demux_eic_irq(unsigned int irq, struct irq_desc *desc)
{
	struct eic *eic = desc->handler_data;
	unsigned long status, pending;
	unsigned int i;

	status = eic_readl(eic, ISR);
	pending = status & eic_readl(eic, IMR);

	while (pending) {
		i = fls(pending) - 1;
		pending &= ~(1 << i);

		generic_handle_irq(i + eic->first_irq);
	}
}