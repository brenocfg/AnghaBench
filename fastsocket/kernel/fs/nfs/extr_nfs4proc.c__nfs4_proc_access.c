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
struct rpc_message {int /*<<< orphan*/  rpc_cred; struct nfs4_accessres* rpc_resp; struct nfs4_accessargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  attr_bitmask; } ;
struct nfs_access_entry {int mask; int /*<<< orphan*/  cred; } ;
struct nfs4_accessres {int /*<<< orphan*/ * fattr; int /*<<< orphan*/  access; int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs4_accessargs {int access; int /*<<< orphan*/  seq_args; int /*<<< orphan*/  bitmask; int /*<<< orphan*/  fh; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int NFS4_ACCESS_DELETE ; 
 int NFS4_ACCESS_EXECUTE ; 
 int NFS4_ACCESS_EXTEND ; 
 int NFS4_ACCESS_LOOKUP ; 
 int NFS4_ACCESS_MODIFY ; 
 int NFS4_ACCESS_READ ; 
 size_t NFSPROC4_CLNT_ACCESS ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_access_set_mask (struct nfs_access_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nfs4_proc_access(struct inode *inode, struct nfs_access_entry *entry)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs4_accessargs args = {
		.fh = NFS_FH(inode),
		.bitmask = server->attr_bitmask,
	};
	struct nfs4_accessres res = {
		.server = server,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_ACCESS],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = entry->cred,
	};
	int mode = entry->mask;
	int status;

	/*
	 * Determine which access bits we want to ask for...
	 */
	if (mode & MAY_READ)
		args.access |= NFS4_ACCESS_READ;
	if (S_ISDIR(inode->i_mode)) {
		if (mode & MAY_WRITE)
			args.access |= NFS4_ACCESS_MODIFY | NFS4_ACCESS_EXTEND | NFS4_ACCESS_DELETE;
		if (mode & MAY_EXEC)
			args.access |= NFS4_ACCESS_LOOKUP;
	} else {
		if (mode & MAY_WRITE)
			args.access |= NFS4_ACCESS_MODIFY | NFS4_ACCESS_EXTEND;
		if (mode & MAY_EXEC)
			args.access |= NFS4_ACCESS_EXECUTE;
	}

	res.fattr = nfs_alloc_fattr();
	if (res.fattr == NULL)
		return -ENOMEM;

	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
	if (!status) {
		nfs_access_set_mask(entry, res.access);
		nfs_refresh_inode(inode, res.fattr);
	}
	nfs_free_fattr(res.fattr);
	return status;
}