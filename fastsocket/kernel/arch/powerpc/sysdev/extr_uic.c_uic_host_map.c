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
struct uic {int dummy; } ;
struct irq_host {struct uic* host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip_data (unsigned int,struct uic*) ; 
 int /*<<< orphan*/  set_irq_type (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uic_irq_chip ; 

__attribute__((used)) static int uic_host_map(struct irq_host *h, unsigned int virq,
			irq_hw_number_t hw)
{
	struct uic *uic = h->host_data;

	set_irq_chip_data(virq, uic);
	/* Despite the name, handle_level_irq() works for both level
	 * and edge irqs on UIC.  FIXME: check this is correct */
	set_irq_chip_and_handler(virq, &uic_irq_chip, handle_level_irq);

	/* Set default irq type */
	set_irq_type(virq, IRQ_TYPE_NONE);

	return 0;
}