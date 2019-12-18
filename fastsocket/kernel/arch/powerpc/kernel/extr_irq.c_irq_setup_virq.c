#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irq_host {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  hwirq; } ;
struct TYPE_4__ {scalar_t__ (* map ) (struct irq_host*,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NOREQUEST ; 
 TYPE_3__* get_irq_desc (unsigned int) ; 
 int /*<<< orphan*/  irq_free_virt (unsigned int,int) ; 
 TYPE_2__* irq_map ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ stub1 (struct irq_host*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irq_setup_virq(struct irq_host *host, unsigned int virq,
			    irq_hw_number_t hwirq)
{
	/* Clear IRQ_NOREQUEST flag */
	get_irq_desc(virq)->status &= ~IRQ_NOREQUEST;

	/* map it */
	smp_wmb();
	irq_map[virq].hwirq = hwirq;
	smp_mb();

	if (host->ops->map(host, virq, hwirq)) {
		pr_debug("irq: -> mapping failed, freeing\n");
		irq_free_virt(virq, 1);
		return -1;
	}

	return 0;
}