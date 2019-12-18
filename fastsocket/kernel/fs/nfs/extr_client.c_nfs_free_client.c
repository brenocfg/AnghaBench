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
struct nfs_client {struct nfs_client* cl_hostname; int /*<<< orphan*/ * cl_machine_cred; int /*<<< orphan*/  cl_rpcclient; TYPE_1__* rpc_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  kfree (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_shutdown_client (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_fscache_release_client_cookie (struct nfs_client*) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_shutdown_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_free_client(struct nfs_client *clp)
{
	dprintk("--> nfs_free_client(%u)\n", clp->rpc_ops->version);

	nfs4_shutdown_client(clp);

	nfs_fscache_release_client_cookie(clp);

	/* -EIO all pending I/O */
	if (!IS_ERR(clp->cl_rpcclient))
		rpc_shutdown_client(clp->cl_rpcclient);

	if (clp->cl_machine_cred != NULL)
		put_rpccred(clp->cl_machine_cred);

	kfree(clp->cl_hostname);
	kfree(clp);

	dprintk("<-- nfs_free_client()\n");
}