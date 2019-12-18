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
struct TYPE_4__ {scalar_t__ ipi_cnt; } ;
struct TYPE_5__ {TYPE_1__ fields; } ;
struct TYPE_6__ {TYPE_2__ int_dword; } ;

/* Variables and functions */
 int NO_IRQ_IGNORE ; 
 int NR_IRQS ; 
 TYPE_3__* get_lppaca () ; 
 scalar_t__ hvlpevent_is_pending () ; 
 int /*<<< orphan*/  iSeries_smp_message_recv () ; 
 scalar_t__ num_pending_irqs ; 
 scalar_t__* pending_irqs ; 
 int /*<<< orphan*/  pending_irqs_lock ; 
 int /*<<< orphan*/  process_hvlpevents () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned int iSeries_get_irq(void)
{
	int irq = NO_IRQ_IGNORE;

#ifdef CONFIG_SMP
	if (get_lppaca()->int_dword.fields.ipi_cnt) {
		get_lppaca()->int_dword.fields.ipi_cnt = 0;
		iSeries_smp_message_recv();
	}
#endif /* CONFIG_SMP */
	if (hvlpevent_is_pending())
		process_hvlpevents();

#ifdef CONFIG_PCI
	if (num_pending_irqs) {
		spin_lock(&pending_irqs_lock);
		for (irq = 0; irq < NR_IRQS; irq++) {
			if (pending_irqs[irq]) {
				pending_irqs[irq]--;
				num_pending_irqs--;
				break;
			}
		}
		spin_unlock(&pending_irqs_lock);
		if (irq >= NR_IRQS)
			irq = NO_IRQ_IGNORE;
	}
#endif

	return irq;
}