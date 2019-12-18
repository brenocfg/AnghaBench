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
struct evtchn_bind_vcpu {int port; unsigned int vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_vcpu ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_vcpu*) ; 
 int /*<<< orphan*/  VALID_EVTCHN (int) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,unsigned int) ; 
 int evtchn_from_irq (unsigned int) ; 
 int /*<<< orphan*/  xen_have_vector_callback ; 
 scalar_t__ xen_hvm_domain () ; 

__attribute__((used)) static int rebind_irq_to_cpu(unsigned irq, unsigned tcpu)
{
	struct evtchn_bind_vcpu bind_vcpu;
	int evtchn = evtchn_from_irq(irq);

	/* events delivered via platform PCI interrupts are always
	 * routed to vcpu 0 */
	if (!VALID_EVTCHN(evtchn) ||
		(xen_hvm_domain() && !xen_have_vector_callback))
		return -1;

	/* Send future instances of this interrupt to other vcpu. */
	bind_vcpu.port = evtchn;
	bind_vcpu.vcpu = tcpu;

	/*
	 * If this fails, it usually just indicates that we're dealing with a
	 * virq or IPI channel, which don't actually need to be rebound. Ignore
	 * it, but don't do the xenlinux-level rebind in that case.
	 */
	if (HYPERVISOR_event_channel_op(EVTCHNOP_bind_vcpu, &bind_vcpu) >= 0)
		bind_evtchn_to_cpu(evtchn, tcpu);

	return 0;
}