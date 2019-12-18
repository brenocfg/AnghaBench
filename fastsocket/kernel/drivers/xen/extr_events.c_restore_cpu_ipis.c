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
struct evtchn_bind_ipi {unsigned int vcpu; int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EVTCHNOP_bind_ipi ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_ipi*) ; 
 int XEN_NR_IPIS ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,unsigned int) ; 
 int* evtchn_to_irq ; 
 int ipi_from_irq (int) ; 
 int /*<<< orphan*/  ipi_to_irq ; 
 int /*<<< orphan*/ * irq_info ; 
 int /*<<< orphan*/  mk_ipi_info (int,int) ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void restore_cpu_ipis(unsigned int cpu)
{
	struct evtchn_bind_ipi bind_ipi;
	int ipi, irq, evtchn;

	for (ipi = 0; ipi < XEN_NR_IPIS; ipi++) {
		if ((irq = per_cpu(ipi_to_irq, cpu)[ipi]) == -1)
			continue;

		BUG_ON(ipi_from_irq(irq) != ipi);

		/* Get a new binding from Xen. */
		bind_ipi.vcpu = cpu;
		if (HYPERVISOR_event_channel_op(EVTCHNOP_bind_ipi,
						&bind_ipi) != 0)
			BUG();
		evtchn = bind_ipi.port;

		/* Record the new mapping. */
		evtchn_to_irq[evtchn] = irq;
		irq_info[irq] = mk_ipi_info(evtchn, ipi);
		bind_evtchn_to_cpu(evtchn, cpu);
	}
}