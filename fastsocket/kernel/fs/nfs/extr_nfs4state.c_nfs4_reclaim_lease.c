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
struct rpc_cred {int dummy; } ;
struct nfs_client {struct rpc_cred* cl_machine_cred; TYPE_1__* cl_mvops; } ;
struct nfs4_state_recovery_ops {int (* establish_clid ) (struct nfs_client*,struct rpc_cred*) ;struct rpc_cred* (* get_clid_cred ) (struct nfs_client*) ;} ;
struct TYPE_2__ {struct nfs4_state_recovery_ops* reboot_recovery_ops; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int ENOENT ; 
 int EPROTONOSUPPORT ; 
 int NFS4ERR_MINOR_VERS_MISMATCH ; 
 int /*<<< orphan*/  nfs4_clear_machine_cred (struct nfs_client*) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* stub1 (struct nfs_client*) ; 
 int stub2 (struct nfs_client*,struct rpc_cred*) ; 

__attribute__((used)) static int nfs4_reclaim_lease(struct nfs_client *clp)
{
	struct rpc_cred *cred;
	const struct nfs4_state_recovery_ops *ops =
		clp->cl_mvops->reboot_recovery_ops;
	int status = -ENOENT;

	cred = ops->get_clid_cred(clp);
	if (cred != NULL) {
		status = ops->establish_clid(clp, cred);
		put_rpccred(cred);
		/* Handle case where the user hasn't set up machine creds */
		if (status == -EACCES && cred == clp->cl_machine_cred) {
			nfs4_clear_machine_cred(clp);
			status = -EAGAIN;
		}
		if (status == -NFS4ERR_MINOR_VERS_MISMATCH)
			status = -EPROTONOSUPPORT;
	}
	return status;
}