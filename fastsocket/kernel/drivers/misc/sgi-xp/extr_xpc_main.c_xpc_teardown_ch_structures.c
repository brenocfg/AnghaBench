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
struct xpc_partition {scalar_t__ setup_state; int /*<<< orphan*/ * channels; int /*<<< orphan*/ * remote_openclose_args; int /*<<< orphan*/ * remote_openclose_args_base; int /*<<< orphan*/  references; int /*<<< orphan*/  teardown_wq; int /*<<< orphan*/  nchannels_active; int /*<<< orphan*/  nchannels_engaged; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown_ch_structures ) (struct xpc_partition*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBUG_ON (int) ; 
 scalar_t__ XPC_P_SS_SETUP ; 
 scalar_t__ XPC_P_SS_TORNDOWN ; 
 scalar_t__ XPC_P_SS_WTEARDOWN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xpc_partition*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ xpc_arch_ops ; 

__attribute__((used)) static void
xpc_teardown_ch_structures(struct xpc_partition *part)
{
	DBUG_ON(atomic_read(&part->nchannels_engaged) != 0);
	DBUG_ON(atomic_read(&part->nchannels_active) != 0);

	/*
	 * Make this partition inaccessible to local processes by marking it
	 * as no longer setup. Then wait before proceeding with the teardown
	 * until all existing references cease.
	 */
	DBUG_ON(part->setup_state != XPC_P_SS_SETUP);
	part->setup_state = XPC_P_SS_WTEARDOWN;

	wait_event(part->teardown_wq, (atomic_read(&part->references) == 0));

	/* now we can begin tearing down the infrastructure */

	xpc_arch_ops.teardown_ch_structures(part);

	kfree(part->remote_openclose_args_base);
	part->remote_openclose_args = NULL;
	kfree(part->channels);
	part->channels = NULL;

	part->setup_state = XPC_P_SS_TORNDOWN;
}