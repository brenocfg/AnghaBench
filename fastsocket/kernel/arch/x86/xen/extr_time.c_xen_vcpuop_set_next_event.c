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
struct vcpu_set_singleshot_timer {int /*<<< orphan*/  flags; int /*<<< orphan*/  timeout_abs_ns; } ;
struct clock_event_device {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CLOCK_EVT_MODE_ONESHOT ; 
 int ETIME ; 
 int HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int,struct vcpu_set_singleshot_timer*) ; 
 int /*<<< orphan*/  VCPUOP_set_singleshot_timer ; 
 int /*<<< orphan*/  VCPU_SSHOTTMR_future ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_abs_timeout (unsigned long) ; 
 int smp_processor_id () ; 

__attribute__((used)) static int xen_vcpuop_set_next_event(unsigned long delta,
				     struct clock_event_device *evt)
{
	int cpu = smp_processor_id();
	struct vcpu_set_singleshot_timer single;
	int ret;

	WARN_ON(evt->mode != CLOCK_EVT_MODE_ONESHOT);

	single.timeout_abs_ns = get_abs_timeout(delta);
	single.flags = VCPU_SSHOTTMR_future;

	ret = HYPERVISOR_vcpu_op(VCPUOP_set_singleshot_timer, cpu, &single);

	BUG_ON(ret != 0 && ret != -ETIME);

	return ret;
}