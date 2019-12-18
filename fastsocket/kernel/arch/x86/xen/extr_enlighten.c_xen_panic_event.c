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
struct sched_shutdown {int /*<<< orphan*/  reason; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HYPERVISOR_sched_op (int /*<<< orphan*/ ,struct sched_shutdown*) ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  SCHEDOP_shutdown ; 
 int /*<<< orphan*/  SHUTDOWN_crash ; 

__attribute__((used)) static int
xen_panic_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct sched_shutdown r = { .reason = SHUTDOWN_crash};

	if (HYPERVISOR_sched_op(SCHEDOP_shutdown, &r))
		BUG();
	return NOTIFY_DONE;
}