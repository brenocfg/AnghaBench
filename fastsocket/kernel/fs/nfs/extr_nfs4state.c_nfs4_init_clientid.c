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
struct TYPE_2__ {scalar_t__ ss_family; } ;
struct nfs_client {int /*<<< orphan*/  cl_state; int /*<<< orphan*/  cl_confirm; int /*<<< orphan*/  cl_clientid; TYPE_1__ cl_addr; } ;
struct nfs4_setclientid_res {int /*<<< orphan*/  confirm; int /*<<< orphan*/  clientid; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  NFS4CLNT_LEASE_CONFIRM ; 
 int /*<<< orphan*/  NFS4_CALLBACK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfs4_proc_setclientid (struct nfs_client*,int /*<<< orphan*/ ,unsigned short,struct rpc_cred*,struct nfs4_setclientid_res*) ; 
 int nfs4_proc_setclientid_confirm (struct nfs_client*,struct nfs4_setclientid_res*,struct rpc_cred*) ; 
 int /*<<< orphan*/  nfs4_schedule_state_renewal (struct nfs_client*) ; 
 unsigned short nfs_callback_tcpport ; 
 unsigned short nfs_callback_tcpport6 ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfs4_init_clientid(struct nfs_client *clp, struct rpc_cred *cred)
{
	struct nfs4_setclientid_res clid = {
		.clientid = clp->cl_clientid,
		.confirm = clp->cl_confirm,
	};
	unsigned short port;
	int status;

	if (test_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state))
		goto do_confirm;
	port = nfs_callback_tcpport;
	if (clp->cl_addr.ss_family == AF_INET6)
		port = nfs_callback_tcpport6;

	status = nfs4_proc_setclientid(clp, NFS4_CALLBACK, port, cred, &clid);
	if (status != 0)
		goto out;
	clp->cl_clientid = clid.clientid;
	clp->cl_confirm = clid.confirm;
	set_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
do_confirm:
	status = nfs4_proc_setclientid_confirm(clp, &clid, cred);
	if (status != 0)
		goto out;
	clear_bit(NFS4CLNT_LEASE_CONFIRM, &clp->cl_state);
	nfs4_schedule_state_renewal(clp);
out:
	return status;
}