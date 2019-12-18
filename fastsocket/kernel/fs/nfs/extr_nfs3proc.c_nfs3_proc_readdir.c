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
typedef  scalar_t__ u64 ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct rpc_cred* rpc_cred; struct nfs3_readdirres* rpc_resp; struct nfs3_readdirargs* rpc_argp; } ;
struct rpc_cred {int dummy; } ;
struct page {int dummy; } ;
struct nfs3_readdirres {int plus; int /*<<< orphan*/ * dir_attr; int /*<<< orphan*/ * verf; } ;
struct nfs3_readdirargs {int plus; unsigned int count; struct page** pages; int /*<<< orphan*/  verf; scalar_t__ cookie; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFS3PROC_READDIR ; 
 size_t NFS3PROC_READDIRPLUS ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/ * NFS_COOKIEVERF (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,char*,int) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 int /*<<< orphan*/ * nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_invalidate_atime (struct inode*) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_readdir(struct dentry *dentry, struct rpc_cred *cred,
		  u64 cookie, struct page **pages, unsigned int count, int plus)
{
	struct inode		*dir = dentry->d_inode;
	__be32			*verf = NFS_COOKIEVERF(dir);
	struct nfs3_readdirargs	arg = {
		.fh		= NFS_FH(dir),
		.cookie		= cookie,
		.verf		= {verf[0], verf[1]},
		.plus		= plus,
		.count		= count,
		.pages		= pages
	};
	struct nfs3_readdirres	res = {
		.verf		= verf,
		.plus		= plus
	};
	struct rpc_message	msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_READDIR],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
		.rpc_cred	= cred
	};
	int status = -ENOMEM;

	if (plus)
		msg.rpc_proc = &nfs3_procedures[NFS3PROC_READDIRPLUS];

	dprintk("NFS call  readdir%s %d\n",
			plus? "plus" : "", (unsigned int) cookie);

	res.dir_attr = nfs_alloc_fattr();
	if (res.dir_attr == NULL)
		goto out;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);

	nfs_invalidate_atime(dir);
	nfs_refresh_inode(dir, res.dir_attr);

	nfs_free_fattr(res.dir_attr);
out:
	dprintk("NFS reply readdir%s: %d\n",
			plus? "plus" : "", status);
	return status;
}