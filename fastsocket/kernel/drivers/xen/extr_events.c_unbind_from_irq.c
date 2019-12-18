#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct evtchn_close {int port; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EVTCHNOP_close ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_close*) ; 
#define  IRQT_IPI 129 
 scalar_t__ IRQT_UNBOUND ; 
#define  IRQT_VIRQ 128 
 scalar_t__ VALID_EVTCHN (int) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_from_evtchn (int) ; 
 int /*<<< orphan*/  dynamic_irq_cleanup (unsigned int) ; 
 int evtchn_from_irq (unsigned int) ; 
 int* evtchn_to_irq ; 
 size_t ipi_from_irq (unsigned int) ; 
 int /*<<< orphan*/  ipi_to_irq ; 
 TYPE_1__* irq_info ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 TYPE_1__ mk_unbound_info () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int type_from_irq (unsigned int) ; 
 size_t virq_from_irq (unsigned int) ; 
 int /*<<< orphan*/  virq_to_irq ; 

__attribute__((used)) static void unbind_from_irq(unsigned int irq)
{
	struct evtchn_close close;
	int evtchn = evtchn_from_irq(irq);

	mutex_lock(&irq_mapping_update_lock);

	if (VALID_EVTCHN(evtchn)) {
		close.port = evtchn;
		if (HYPERVISOR_event_channel_op(EVTCHNOP_close, &close) != 0)
			BUG();

		switch (type_from_irq(irq)) {
		case IRQT_VIRQ:
			per_cpu(virq_to_irq, cpu_from_evtchn(evtchn))
				[virq_from_irq(irq)] = -1;
			break;
		case IRQT_IPI:
			per_cpu(ipi_to_irq, cpu_from_evtchn(evtchn))
				[ipi_from_irq(irq)] = -1;
			break;
		default:
			break;
		}

		/* Closed ports are implicitly re-bound to VCPU0. */
		bind_evtchn_to_cpu(evtchn, 0);

		evtchn_to_irq[evtchn] = -1;
	}

	if (irq_info[irq].type != IRQT_UNBOUND) {
		irq_info[irq] = mk_unbound_info();

		dynamic_irq_cleanup(irq);
	}

	mutex_unlock(&irq_mapping_update_lock);
}