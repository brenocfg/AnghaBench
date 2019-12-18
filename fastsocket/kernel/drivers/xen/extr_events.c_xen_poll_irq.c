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
struct sched_poll {int nr_ports; int /*<<< orphan*/  ports; scalar_t__ timeout; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HYPERVISOR_sched_op (int /*<<< orphan*/ ,struct sched_poll*) ; 
 int /*<<< orphan*/  SCHEDOP_poll ; 
 scalar_t__ VALID_EVTCHN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtchn_from_irq (int) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xen_poll_irq(int irq)
{
	evtchn_port_t evtchn = evtchn_from_irq(irq);

	if (VALID_EVTCHN(evtchn)) {
		struct sched_poll poll;

		poll.nr_ports = 1;
		poll.timeout = 0;
		set_xen_guest_handle(poll.ports, &evtchn);

		if (HYPERVISOR_sched_op(SCHEDOP_poll, &poll) != 0)
			BUG();
	}
}