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
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socrates_fpga_pic_chip ; 

__attribute__((used)) static int socrates_fpga_pic_host_map(struct irq_host *h, unsigned int virq,
		irq_hw_number_t hwirq)
{
	/* All interrupts are LEVEL sensitive */
	get_irq_desc(virq)->status |= IRQ_LEVEL;
	set_irq_chip_and_handler(virq, &socrates_fpga_pic_chip,
			handle_fasteoi_irq);

	return 0;
}