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
struct ipc_namespace {int /*<<< orphan*/  proc_inum; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ipc_namespace* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPCNS_CREATED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipcns_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipc_namespace*) ; 
 struct ipc_namespace* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mq_init_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  msg_init_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  nr_ipc_ns ; 
 int proc_alloc_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_free_inum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_ipcns_notifier (struct ipc_namespace*) ; 
 int /*<<< orphan*/  sem_init_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  shm_init_ns (struct ipc_namespace*) ; 

__attribute__((used)) static struct ipc_namespace *create_ipc_ns(void)
{
	struct ipc_namespace *ns;
	int err;

	ns = kmalloc(sizeof(struct ipc_namespace), GFP_KERNEL);
	if (ns == NULL)
		return ERR_PTR(-ENOMEM);

	err = proc_alloc_inum(&ns->proc_inum);
	if (err) {
		kfree(ns);
		return ERR_PTR(err);
	}

	atomic_set(&ns->count, 1);
	err = mq_init_ns(ns);
	if (err) {
		proc_free_inum(ns->proc_inum);
		kfree(ns);
		return ERR_PTR(err);
	}
	atomic_inc(&nr_ipc_ns);

	sem_init_ns(ns);
	msg_init_ns(ns);
	shm_init_ns(ns);

	/*
	 * msgmni has already been computed for the new ipc ns.
	 * Thus, do the ipcns creation notification before registering that
	 * new ipcns in the chain.
	 */
	ipcns_notify(IPCNS_CREATED);
	register_ipcns_notifier(ns);

	return ns;
}