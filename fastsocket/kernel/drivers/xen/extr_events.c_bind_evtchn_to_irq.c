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

/* Variables and functions */
 int* evtchn_to_irq ; 
 int find_unbound_irq () ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/ * irq_info ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  mk_evtchn_info (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xen_dynamic_chip ; 

int bind_evtchn_to_irq(unsigned int evtchn)
{
	int irq;

	mutex_lock(&irq_mapping_update_lock);

	irq = evtchn_to_irq[evtchn];

	if (irq == -1) {
		irq = find_unbound_irq();

		set_irq_chip_and_handler_name(irq, &xen_dynamic_chip,
					      handle_edge_irq, "event");

		evtchn_to_irq[evtchn] = irq;
		irq_info[irq] = mk_evtchn_info(evtchn);
	}

	mutex_unlock(&irq_mapping_update_lock);

	return irq;
}