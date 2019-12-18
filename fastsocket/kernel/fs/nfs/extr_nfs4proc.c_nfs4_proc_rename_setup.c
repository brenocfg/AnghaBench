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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct nfs_renameres* rpc_resp; struct nfs_renameargs* rpc_argp; } ;
struct nfs_server {int dummy; } ;
struct nfs_renameres {int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs_renameargs {int /*<<< orphan*/  seq_args; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_RENAME ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs41_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

__attribute__((used)) static void nfs4_proc_rename_setup(struct rpc_message *msg, struct inode *dir)
{
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs_renameargs *arg = msg->rpc_argp;
	struct nfs_renameres *res = msg->rpc_resp;

	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RENAME];
	res->server = server;
	nfs41_init_sequence(&arg->seq_args, &res->seq_res, 1);
}