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
struct vcpu_info {int evtchn_upcall_pending; int /*<<< orphan*/  evtchn_pending_sel; } ;
struct shared_info {int /*<<< orphan*/ * evtchn_pending; int /*<<< orphan*/ * evtchn_mask; } ;
struct evtchn_unmask {int port; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EVTCHNOP_unmask ; 
 int /*<<< orphan*/  HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_unmask*) ; 
 struct shared_info* HYPERVISOR_shared_info ; 
 struct vcpu_info* __get_cpu_var (int /*<<< orphan*/ ) ; 
 unsigned int cpu_from_evtchn (int) ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  sync_clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ sync_test_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_vcpu ; 

__attribute__((used)) static void unmask_evtchn(int port)
{
	struct shared_info *s = HYPERVISOR_shared_info;
	unsigned int cpu = get_cpu();

	BUG_ON(!irqs_disabled());

	/* Slow path (hypercall) if this is a non-local port. */
	if (unlikely(cpu != cpu_from_evtchn(port))) {
		struct evtchn_unmask unmask = { .port = port };
		(void)HYPERVISOR_event_channel_op(EVTCHNOP_unmask, &unmask);
	} else {
		struct vcpu_info *vcpu_info = __get_cpu_var(xen_vcpu);

		sync_clear_bit(port, &s->evtchn_mask[0]);

		/*
		 * The following is basically the equivalent of
		 * 'hw_resend_irq'. Just like a real IO-APIC we 'lose
		 * the interrupt edge' if the channel is masked.
		 */
		if (sync_test_bit(port, &s->evtchn_pending[0]) &&
		    !sync_test_and_set_bit(port / BITS_PER_LONG,
					   &vcpu_info->evtchn_pending_sel))
			vcpu_info->evtchn_upcall_pending = 1;
	}

	put_cpu();
}