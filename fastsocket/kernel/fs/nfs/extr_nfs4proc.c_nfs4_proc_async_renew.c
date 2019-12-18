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
struct rpc_message {struct rpc_cred* rpc_cred; struct nfs_client* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct nfs_client {int /*<<< orphan*/  cl_rpcclient; int /*<<< orphan*/  cl_count; } ;
struct nfs4_renewdata {int /*<<< orphan*/  timestamp; struct nfs_client* client; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NFSPROC4_CLNT_RENEW ; 
 int /*<<< orphan*/  RPC_TASK_SOFT ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct nfs4_renewdata* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_renew_ops ; 
 int rpc_call_async (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs4_renewdata*) ; 

__attribute__((used)) static int nfs4_proc_async_renew(struct nfs_client *clp, struct rpc_cred *cred, unsigned renew_flags)
{
	struct rpc_message msg = {
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_RENEW],
		.rpc_argp	= clp,
		.rpc_cred	= cred,
	};
	struct nfs4_renewdata *data;

	if (renew_flags == 0)
		return 0;
	if (!atomic_inc_not_zero(&clp->cl_count))
		return -EIO;
	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;
	data->client = clp;
	data->timestamp = jiffies;
	return rpc_call_async(clp->cl_rpcclient, &msg, RPC_TASK_SOFT,
			&nfs4_renew_ops, data);
}