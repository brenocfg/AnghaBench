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
struct qstr {int /*<<< orphan*/  name; } ;
struct nfs_renameres {int /*<<< orphan*/ * new_fattr; int /*<<< orphan*/ * old_fattr; } ;
struct nfs_renameargs {struct qstr* new_name; int /*<<< orphan*/  new_dir; struct qstr* old_name; int /*<<< orphan*/  old_dir; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFS3PROC_RENAME ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 void* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_rename(struct inode *old_dir, struct qstr *old_name,
		 struct inode *new_dir, struct qstr *new_name)
{
	struct nfs_renameargs	arg = {
		.old_dir	= NFS_FH(old_dir),
		.old_name	= old_name,
		.new_dir	= NFS_FH(new_dir),
		.new_name	= new_name,
	};
	struct nfs_renameres res;
	struct rpc_message msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_RENAME],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	};
	int status = -ENOMEM;

	dprintk("NFS call  rename %s -> %s\n", old_name->name, new_name->name);

	res.old_fattr = nfs_alloc_fattr();
	res.new_fattr = nfs_alloc_fattr();
	if (res.old_fattr == NULL || res.new_fattr == NULL)
		goto out;

	status = rpc_call_sync(NFS_CLIENT(old_dir), &msg, 0);
	nfs_post_op_update_inode(old_dir, res.old_fattr);
	nfs_post_op_update_inode(new_dir, res.new_fattr);
out:
	nfs_free_fattr(res.old_fattr);
	nfs_free_fattr(res.new_fattr);
	dprintk("NFS reply rename: %d\n", status);
	return status;
}