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
struct evtchn_bind_virq {unsigned int virq; unsigned int vcpu; int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EVTCHNOP_bind_virq ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_virq*) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,unsigned int) ; 
 int* evtchn_to_irq ; 
 int find_unbound_irq () ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/ * irq_info ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  mk_virq_info (int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_irq_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  virq_to_irq ; 
 int /*<<< orphan*/  xen_percpu_chip ; 

__attribute__((used)) static int bind_virq_to_irq(unsigned int virq, unsigned int cpu)
{
	struct evtchn_bind_virq bind_virq;
	int evtchn, irq;

	mutex_lock(&irq_mapping_update_lock);

	irq = per_cpu(virq_to_irq, cpu)[virq];

	if (irq == -1) {
		irq = find_unbound_irq();

		set_irq_chip_and_handler_name(irq, &xen_percpu_chip,
					      handle_percpu_irq, "virq");

		bind_virq.virq = virq;
		bind_virq.vcpu = cpu;
		if (HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq,
						&bind_virq) != 0)
			BUG();
		evtchn = bind_virq.port;

		evtchn_to_irq[evtchn] = irq;
		irq_info[irq] = mk_virq_info(evtchn, virq);

		per_cpu(virq_to_irq, cpu)[virq] = irq;

		bind_evtchn_to_cpu(evtchn, cpu);
	}

	mutex_unlock(&irq_mapping_update_lock);

	return irq;
}