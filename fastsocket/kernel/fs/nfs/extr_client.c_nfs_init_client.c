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
struct rpc_timeout {int dummy; } ;
struct nfs_client {scalar_t__ cl_cons_state; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 scalar_t__ NFS_CS_READY ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int nfs_create_rpc_client (struct nfs_client*,struct rpc_timeout const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_mark_client_ready (struct nfs_client*,int) ; 

int nfs_init_client(struct nfs_client *clp, const struct rpc_timeout *timeparms,
		    const char *ip_addr, rpc_authflavor_t authflavour,
		    int noresvport)
{
	int error;

	if (clp->cl_cons_state == NFS_CS_READY) {
		/* the client is already initialised */
		dprintk("<-- nfs_init_client() = 0 [already %p]\n", clp);
		return 0;
	}

	/*
	 * Create a client RPC handle for doing FSSTAT with UNIX auth only
	 * - RFC 2623, sec 2.3.2
	 */
	error = nfs_create_rpc_client(clp, timeparms, RPC_AUTH_UNIX,
				      0, noresvport);
	if (error < 0)
		goto error;
	nfs_mark_client_ready(clp, NFS_CS_READY);
	return 0;

error:
	nfs_mark_client_ready(clp, error);
	dprintk("<-- nfs_init_client() = xerror %d\n", error);
	return error;
}