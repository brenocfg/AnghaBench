#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_port_t ;
typedef  TYPE_2__* ipc_mqueue_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {scalar_t__ imq_seqno; } ;
struct TYPE_9__ {scalar_t__ ip_in_pset; TYPE_2__ ip_messages; scalar_t__ ip_strict_guard; scalar_t__ ip_guarded; scalar_t__ ip_context; scalar_t__ ip_mscount; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  imq_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_mqueue_changed (TYPE_2__*) ; 
 scalar_t__ ipc_mqueue_destroy_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_pset_remove_from_all (TYPE_1__*) ; 

boolean_t
ipc_port_clear_receiver(
	ipc_port_t	port,
	boolean_t	should_destroy)
{
	ipc_mqueue_t	mqueue = &port->ip_messages;
	boolean_t	reap_messages = FALSE;

	/*
	 * Pull ourselves out of any sets to which we belong.
	 * We hold the port locked, so even though this acquires and releases
	 * the mqueue lock, we know we won't be added to any other sets.
	 */
	if (port->ip_in_pset != 0) {
		ipc_pset_remove_from_all(port);
		assert(port->ip_in_pset == 0);
	}

	/*
	 * Send anyone waiting on the port's queue directly away.
	 * Also clear the mscount and seqno.
	 */
	imq_lock(mqueue);
	ipc_mqueue_changed(mqueue);
	port->ip_mscount = 0;
	mqueue->imq_seqno = 0;
	port->ip_context = port->ip_guarded = port->ip_strict_guard = 0;

	if (should_destroy) {
		/*
		 * Mark the mqueue invalid, preventing further send/receive
		 * operations from succeeding. It's important for this to be
		 * done under the same lock hold as the ipc_mqueue_changed
		 * call to avoid additional threads blocking on an mqueue
		 * that's being destroyed.
		 */
		reap_messages = ipc_mqueue_destroy_locked(mqueue);
	}

	imq_unlock(&port->ip_messages);

	return reap_messages;
}