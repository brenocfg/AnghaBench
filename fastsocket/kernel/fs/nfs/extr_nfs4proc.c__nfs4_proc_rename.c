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
struct rpc_message {struct nfs_renameres* rpc_resp; struct nfs_renameargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_renameres {int /*<<< orphan*/  new_cinfo; int /*<<< orphan*/  old_cinfo; int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs_renameargs {int /*<<< orphan*/  seq_args; struct qstr* new_name; struct qstr* old_name; int /*<<< orphan*/  new_dir; int /*<<< orphan*/  old_dir; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFSPROC4_CLNT_RENAME ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  update_changeattr (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nfs4_proc_rename(struct inode *old_dir, struct qstr *old_name,
		struct inode *new_dir, struct qstr *new_name)
{
	struct nfs_server *server = NFS_SERVER(old_dir);
	struct nfs_renameargs arg = {
		.old_dir = NFS_FH(old_dir),
		.new_dir = NFS_FH(new_dir),
		.old_name = old_name,
		.new_name = new_name,
	};
	struct nfs_renameres res = {
		.server = server,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RENAME],
		.rpc_argp = &arg,
		.rpc_resp = &res,
	};
	int status = -ENOMEM;
	
	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	if (!status) {
		update_changeattr(old_dir, &res.old_cinfo);
		update_changeattr(new_dir, &res.new_cinfo);
	}
	return status;
}