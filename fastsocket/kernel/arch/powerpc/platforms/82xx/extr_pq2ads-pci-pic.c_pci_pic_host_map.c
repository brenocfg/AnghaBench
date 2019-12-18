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
struct irq_host {int /*<<< orphan*/  host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL ; 
 TYPE_1__* get_irq_desc (unsigned int) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  pq2ads_pci_ic ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip_data (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_pic_host_map(struct irq_host *h, unsigned int virq,
			    irq_hw_number_t hw)
{
	get_irq_desc(virq)->status |= IRQ_LEVEL;
	set_irq_chip_data(virq, h->host_data);
	set_irq_chip_and_handler(virq, &pq2ads_pci_ic, handle_level_irq);
	return 0;
}