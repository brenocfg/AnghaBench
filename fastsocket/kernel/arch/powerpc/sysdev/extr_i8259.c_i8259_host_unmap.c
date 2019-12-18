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
struct irq_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i8259_mask_irq (unsigned int) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (unsigned int) ; 

__attribute__((used)) static void i8259_host_unmap(struct irq_host *h, unsigned int virq)
{
	/* Make sure irq is masked in hardware */
	i8259_mask_irq(virq);

	/* remove chip and handler */
	set_irq_chip_and_handler(virq, NULL, NULL);

	/* Make sure it's completed */
	synchronize_irq(virq);
}