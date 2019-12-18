#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lg_cpu {int /*<<< orphan*/ * hcall; int /*<<< orphan*/  pending_notify; TYPE_1__* lg; } ;
struct TYPE_2__ {int /*<<< orphan*/  lguest_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_async_hcalls (struct lg_cpu*) ; 
 int /*<<< orphan*/  do_hcall (struct lg_cpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize (struct lg_cpu*) ; 
 scalar_t__ unlikely (int) ; 

void do_hypercalls(struct lg_cpu *cpu)
{
	/* Not initialized yet?  This hypercall must do it. */
	if (unlikely(!cpu->lg->lguest_data)) {
		/* Set up the "struct lguest_data" */
		initialize(cpu);
		/* Hcall is done. */
		cpu->hcall = NULL;
		return;
	}

	/*
	 * The Guest has initialized.
	 *
	 * Look in the hypercall ring for the async hypercalls:
	 */
	do_async_hcalls(cpu);

	/*
	 * If we stopped reading the hypercall ring because the Guest did a
	 * NOTIFY to the Launcher, we want to return now.  Otherwise we do
	 * the hypercall.
	 */
	if (!cpu->pending_notify) {
		do_hcall(cpu, cpu->hcall);
		/*
		 * Tricky point: we reset the hcall pointer to mark the
		 * hypercall as "done".  We use the hcall pointer rather than
		 * the trap number to indicate a hypercall is pending.
		 * Normally it doesn't matter: the Guest will run again and
		 * update the trap number before we come back here.
		 *
		 * However, if we are signalled or the Guest sends I/O to the
		 * Launcher, the run_guest() loop will exit without running the
		 * Guest.  When it comes back it would try to re-run the
		 * hypercall.  Finding that bug sucked.
		 */
		cpu->hcall = NULL;
	}
}