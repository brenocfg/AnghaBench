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
struct task_struct {int dummy; } ;
struct nfs_client {int /*<<< orphan*/  cl_rpcclient; int /*<<< orphan*/  cl_count; int /*<<< orphan*/  cl_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  NFS4CLNT_MANAGER_RUNNING ; 
 int /*<<< orphan*/  RPC_DISPLAY_ADDR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct nfs_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_clear_state_manager_bit (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_run_state_manager ; 
 int /*<<< orphan*/  nfs_put_client (struct nfs_client*) ; 
 int /*<<< orphan*/  rpc_peeraddr2str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfs4_schedule_state_manager(struct nfs_client *clp)
{
	struct task_struct *task;

	if (test_and_set_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) != 0)
		return;
	__module_get(THIS_MODULE);
	atomic_inc(&clp->cl_count);
	task = kthread_run(nfs4_run_state_manager, clp, "%s-manager",
				rpc_peeraddr2str(clp->cl_rpcclient,
							RPC_DISPLAY_ADDR));
	if (!IS_ERR(task))
		return;
	nfs4_clear_state_manager_bit(clp);
	nfs_put_client(clp);
	module_put(THIS_MODULE);
}