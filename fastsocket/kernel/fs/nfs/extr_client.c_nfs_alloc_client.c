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
struct rpc_cred {int dummy; } ;
struct nfs_client_initdata {size_t minorversion; int /*<<< orphan*/  proto; scalar_t__ hostname; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; int /*<<< orphan*/  rpc_ops; } ;
struct nfs_client {int cl_state; size_t cl_minorversion; struct rpc_cred* cl_machine_cred; int /*<<< orphan*/  cl_mvops; int /*<<< orphan*/  cl_boot_time; int /*<<< orphan*/  cl_rpcwaitq; int /*<<< orphan*/  cl_renewd; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_proto; struct nfs_client* cl_rpcclient; int /*<<< orphan*/  cl_superblocks; int /*<<< orphan*/  cl_hostname; int /*<<< orphan*/  cl_addrlen; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cons_state; int /*<<< orphan*/  cl_count; int /*<<< orphan*/  rpc_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct nfs_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR (struct rpc_cred*) ; 
 int NFS4CLNT_LEASE_EXPIRED ; 
 int /*<<< orphan*/  NFS_CS_INITING ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct nfs_client*) ; 
 int /*<<< orphan*/  kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 struct nfs_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_renew_state ; 
 int /*<<< orphan*/  nfs_fscache_get_client_cookie (struct nfs_client*) ; 
 int nfs_get_cb_ident_idr (struct nfs_client*,size_t) ; 
 int /*<<< orphan*/ * nfs_v4_minor_ops ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 struct rpc_cred* rpc_lookup_machine_cred () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_client *nfs_alloc_client(const struct nfs_client_initdata *cl_init)
{
	struct nfs_client *clp;
	struct rpc_cred *cred;
	int err = -ENOMEM;

	if ((clp = kzalloc(sizeof(*clp), GFP_KERNEL)) == NULL)
		goto error_0;

	clp->rpc_ops = cl_init->rpc_ops;

	atomic_set(&clp->cl_count, 1);
	clp->cl_cons_state = NFS_CS_INITING;

	memcpy(&clp->cl_addr, cl_init->addr, cl_init->addrlen);
	clp->cl_addrlen = cl_init->addrlen;

	if (cl_init->hostname) {
		err = -ENOMEM;
		clp->cl_hostname = kstrdup(cl_init->hostname, GFP_KERNEL);
		if (!clp->cl_hostname)
			goto error_cleanup;
	}

	INIT_LIST_HEAD(&clp->cl_superblocks);
	clp->cl_rpcclient = ERR_PTR(-EINVAL);

	clp->cl_proto = cl_init->proto;

#ifdef CONFIG_NFS_V4
	err = nfs_get_cb_ident_idr(clp, cl_init->minorversion);
	if (err)
		goto error_cleanup;

	spin_lock_init(&clp->cl_lock);
	INIT_DELAYED_WORK(&clp->cl_renewd, nfs4_renew_state);
	rpc_init_wait_queue(&clp->cl_rpcwaitq, "NFS client");
	clp->cl_boot_time = CURRENT_TIME;
	clp->cl_state = 1 << NFS4CLNT_LEASE_EXPIRED;
	clp->cl_minorversion = cl_init->minorversion;
	clp->cl_mvops = nfs_v4_minor_ops[cl_init->minorversion];
#endif
	cred = rpc_lookup_machine_cred();
	if (!IS_ERR(cred))
		clp->cl_machine_cred = cred;
	nfs_fscache_get_client_cookie(clp);

	return clp;

error_cleanup:
	kfree(clp);
error_0:
	return ERR_PTR(err);
}