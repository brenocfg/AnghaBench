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
struct ipc_namespace {int /*<<< orphan*/  proc_inum; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCNS_REMOVED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcns_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipc_namespace*) ; 
 int /*<<< orphan*/  msg_exit_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  nr_ipc_ns ; 
 int /*<<< orphan*/  proc_free_inum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_exit_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  shm_exit_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  unregister_ipcns_notifier (struct ipc_namespace*) ; 

__attribute__((used)) static void free_ipc_ns(struct ipc_namespace *ns)
{
	/*
	 * Unregistering the hotplug notifier at the beginning guarantees
	 * that the ipc namespace won't be freed while we are inside the
	 * callback routine. Since the blocking_notifier_chain_XXX routines
	 * hold a rw lock on the notifier list, unregister_ipcns_notifier()
	 * won't take the rw lock before blocking_notifier_call_chain() has
	 * released the rd lock.
	 */
	unregister_ipcns_notifier(ns);
	sem_exit_ns(ns);
	msg_exit_ns(ns);
	shm_exit_ns(ns);
	proc_free_inum(ns->proc_inum);
	kfree(ns);
	atomic_dec(&nr_ipc_ns);

	/*
	 * Do the ipcns removal notification after decrementing nr_ipc_ns in
	 * order to have a correct value when recomputing msgmni.
	 */
	ipcns_notify(IPCNS_REMOVED);
}