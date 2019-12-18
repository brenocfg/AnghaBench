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
struct TYPE_2__ {int /*<<< orphan*/  action; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xen_register_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int late_irq_cnt ; 
 TYPE_1__* saved_percpu_irqs ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int xen_slab_ready ; 

__attribute__((used)) static void
xen_bind_early_percpu_irq(void)
{
	int i;

	xen_slab_ready = 1;
	/* There's no race when accessing this cached array, since only
	 * BSP will face with such step shortly
	 */
	for (i = 0; i < late_irq_cnt; i++)
		__xen_register_percpu_irq(smp_processor_id(),
					  saved_percpu_irqs[i].irq,
					  saved_percpu_irqs[i].action, 0);
}