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
struct rpc_message {struct nfs3_linkres* rpc_resp; struct nfs3_linkargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int name; int /*<<< orphan*/  len; } ;
struct nfs3_linkres {int /*<<< orphan*/ * fattr; int /*<<< orphan*/ * dir_attr; } ;
struct nfs3_linkargs {int toname; int /*<<< orphan*/  tolen; int /*<<< orphan*/  tofh; int /*<<< orphan*/  fromfh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFS3PROC_LINK ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 void* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_link(struct inode *inode, struct inode *dir, struct qstr *name)
{
	struct nfs3_linkargs	arg = {
		.fromfh		= NFS_FH(inode),
		.tofh		= NFS_FH(dir),
		.toname		= name->name,
		.tolen		= name->len
	};
	struct nfs3_linkres	res;
	struct rpc_message msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_LINK],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	};
	int status = -ENOMEM;

	dprintk("NFS call  link %s\n", name->name);
	res.fattr = nfs_alloc_fattr();
	res.dir_attr = nfs_alloc_fattr();
	if (res.fattr == NULL || res.dir_attr == NULL)
		goto out;

	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	nfs_post_op_update_inode(dir, res.dir_attr);
	nfs_post_op_update_inode(inode, res.fattr);
out:
	nfs_free_fattr(res.dir_attr);
	nfs_free_fattr(res.fattr);
	dprintk("NFS reply link: %d\n", status);
	return status;
}