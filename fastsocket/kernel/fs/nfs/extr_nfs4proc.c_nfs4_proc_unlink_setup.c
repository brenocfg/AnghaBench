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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct nfs_removeres* rpc_resp; struct nfs_removeargs* rpc_argp; } ;
struct nfs_server {int dummy; } ;
struct nfs_removeres {int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs_removeargs {int /*<<< orphan*/  seq_args; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_REMOVE ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs41_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

__attribute__((used)) static void nfs4_proc_unlink_setup(struct rpc_message *msg, struct inode *dir)
{
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs_removeargs *args = msg->rpc_argp;
	struct nfs_removeres *res = msg->rpc_resp;

	res->server = server;
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_REMOVE];
	nfs41_init_sequence(&args->seq_args, &res->seq_res, 1);
}