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
struct rpc_message {struct rpc_cred* rpc_cred; struct nfs_fsinfo* rpc_resp; struct nfs4_setclientid_res* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct nfs_fsinfo {int lease_time; } ;
struct nfs_client {int cl_lease_time; unsigned long cl_last_renewal; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_rpcclient; } ;
struct nfs4_setclientid_res {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 size_t NFSPROC4_CLNT_SETCLIENTID_CONFIRM ; 
 int /*<<< orphan*/  RPC_TASK_TIMEOUT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int nfs4_proc_setclientid_confirm(struct nfs_client *clp,
		struct nfs4_setclientid_res *arg,
		struct rpc_cred *cred)
{
	struct nfs_fsinfo fsinfo;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SETCLIENTID_CONFIRM],
		.rpc_argp = arg,
		.rpc_resp = &fsinfo,
		.rpc_cred = cred,
	};
	unsigned long now;
	int status;

	now = jiffies;
	status = rpc_call_sync(clp->cl_rpcclient, &msg, RPC_TASK_TIMEOUT);
	if (status == 0) {
		spin_lock(&clp->cl_lock);
		clp->cl_lease_time = fsinfo.lease_time * HZ;
		clp->cl_last_renewal = now;
		spin_unlock(&clp->cl_lock);
	}
	return status;
}