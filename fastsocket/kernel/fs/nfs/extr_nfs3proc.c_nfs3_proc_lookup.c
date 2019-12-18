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
struct rpc_message {struct nfs_fattr* rpc_resp; struct nfs_fh* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int dummy; } ;
struct qstr {int name; int /*<<< orphan*/  len; } ;
struct nfs_fh {int name; int /*<<< orphan*/  len; int /*<<< orphan*/  fh; } ;
struct nfs_fattr {int valid; int /*<<< orphan*/ * dir_attr; struct nfs_fattr* fattr; struct nfs_fh* fh; } ;
struct nfs3_diropres {int valid; int /*<<< orphan*/ * dir_attr; struct nfs3_diropres* fattr; struct nfs_fh* fh; } ;
struct nfs3_diropargs {int name; int /*<<< orphan*/  len; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFS3PROC_GETATTR ; 
 size_t NFS3PROC_LOOKUP ; 
 int NFS_ATTR_FATTR ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 int /*<<< orphan*/ * nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_lookup(struct rpc_clnt *clnt, struct inode *dir, struct qstr *name,
		 struct nfs_fh *fhandle, struct nfs_fattr *fattr)
{
	struct nfs3_diropargs	arg = {
		.fh		= NFS_FH(dir),
		.name		= name->name,
		.len		= name->len
	};
	struct nfs3_diropres	res = {
		.fh		= fhandle,
		.fattr		= fattr
	};
	struct rpc_message msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_LOOKUP],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	};
	int			status;

	dprintk("NFS call  lookup %s\n", name->name);
	res.dir_attr = nfs_alloc_fattr();
	if (res.dir_attr == NULL)
		return -ENOMEM;

	nfs_fattr_init(fattr);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_refresh_inode(dir, res.dir_attr);
	if (status >= 0 && !(fattr->valid & NFS_ATTR_FATTR)) {
		msg.rpc_proc = &nfs3_procedures[NFS3PROC_GETATTR];
		msg.rpc_argp = fhandle;
		msg.rpc_resp = fattr;
		status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	}
	nfs_free_fattr(res.dir_attr);
	dprintk("NFS reply lookup: %d\n", status);
	return status;
}