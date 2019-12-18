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
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 int /*<<< orphan*/  HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCPUOP_stop_periodic_timer ; 
 int /*<<< orphan*/  VCPUOP_stop_singleshot_timer ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void xen_vcpuop_set_mode(enum clock_event_mode mode,
				struct clock_event_device *evt)
{
	int cpu = smp_processor_id();

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		WARN_ON(1);	/* unsupported */
		break;

	case CLOCK_EVT_MODE_ONESHOT:
		if (HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_timer, cpu, NULL))
			BUG();
		break;

	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
		if (HYPERVISOR_vcpu_op(VCPUOP_stop_singleshot_timer, cpu, NULL) ||
		    HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_timer, cpu, NULL))
			BUG();
		break;
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}