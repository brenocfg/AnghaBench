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
struct rpc_message {struct nfs_fattr* rpc_resp; struct nfs3_diropargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int name; int /*<<< orphan*/  len; } ;
struct nfs_fattr {int dummy; } ;
struct nfs3_diropargs {int name; int /*<<< orphan*/  len; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFS3PROC_RMDIR ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (struct inode*,struct nfs_fattr*) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_rmdir(struct inode *dir, struct qstr *name)
{
	struct nfs_fattr	*dir_attr;
	struct nfs3_diropargs	arg = {
		.fh		= NFS_FH(dir),
		.name		= name->name,
		.len		= name->len
	};
	struct rpc_message msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_RMDIR],
		.rpc_argp	= &arg,
	};
	int status = -ENOMEM;

	dprintk("NFS call  rmdir %s\n", name->name);
	dir_attr = nfs_alloc_fattr();
	if (dir_attr == NULL)
		goto out;

	msg.rpc_resp = dir_attr;
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_post_op_update_inode(dir, dir_attr);
	nfs_free_fattr(dir_attr);
out:
	dprintk("NFS reply rmdir: %d\n", status);
	return status;
}