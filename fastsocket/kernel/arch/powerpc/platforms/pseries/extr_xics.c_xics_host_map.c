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
struct irq_host {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 TYPE_1__* get_irq_desc (unsigned int) ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  irq_radix_revmap_insert (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xics_host ; 
 int /*<<< orphan*/  xics_irq_chip ; 

__attribute__((used)) static int xics_host_map(struct irq_host *h, unsigned int virq,
			 irq_hw_number_t hw)
{
	pr_devel("xics: map virq %d, hwirq 0x%lx\n", virq, hw);

	/* Insert the interrupt mapping into the radix tree for fast lookup */
	irq_radix_revmap_insert(xics_host, virq, hw);

	get_irq_desc(virq)->status |= IRQ_LEVEL;
	set_irq_chip_and_handler(virq, xics_irq_chip, handle_fasteoi_irq);
	return 0;
}