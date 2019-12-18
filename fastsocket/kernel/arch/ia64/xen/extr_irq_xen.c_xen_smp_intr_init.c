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
struct callback_register {int /*<<< orphan*/  address; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALLBACKOP_register ; 
 int /*<<< orphan*/  CALLBACKTYPE_event ; 
 int /*<<< orphan*/  HYPERVISOR_callback_op (int /*<<< orphan*/ ,struct callback_register*) ; 
 int /*<<< orphan*/  register_cpu_notifier (int /*<<< orphan*/ *) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  unbind_evtchn_notifier ; 

void xen_smp_intr_init(void)
{
#ifdef CONFIG_SMP
	unsigned int cpu = smp_processor_id();
	struct callback_register event = {
		.type = CALLBACKTYPE_event,
		.address = { .ip = (unsigned long)&xen_event_callback },
	};

	if (cpu == 0) {
		/* Initialization was already done for boot cpu.  */
#ifdef CONFIG_HOTPLUG_CPU
		/* Register the notifier only once.  */
		register_cpu_notifier(&unbind_evtchn_notifier);
#endif
		return;
	}

	/* This should be piggyback when setup vcpu guest context */
	BUG_ON(HYPERVISOR_callback_op(CALLBACKOP_register, &event));
#endif /* CONFIG_SMP */
}