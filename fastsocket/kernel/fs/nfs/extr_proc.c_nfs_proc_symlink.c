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
struct rpc_message {struct nfs_symlinkargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct page {int dummy; } ;
struct nfs_symlinkargs {int fromname; unsigned int pathlen; struct iattr* sattr; struct page** pages; int /*<<< orphan*/  fromlen; int /*<<< orphan*/  fromfh; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct TYPE_2__ {int name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 unsigned int NFS2_MAXPATHLEN ; 
 size_t NFSPROC_SYMLINK ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 struct nfs_fh* nfs_alloc_fhandle () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_free_fhandle (struct nfs_fh*) ; 
 int nfs_instantiate (struct dentry*,struct nfs_fh*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_symlink(struct inode *dir, struct dentry *dentry, struct page *page,
		 unsigned int len, struct iattr *sattr)
{
	struct nfs_fh *fh;
	struct nfs_fattr *fattr;
	struct nfs_symlinkargs	arg = {
		.fromfh		= NFS_FH(dir),
		.fromname	= dentry->d_name.name,
		.fromlen	= dentry->d_name.len,
		.pages		= &page,
		.pathlen	= len,
		.sattr		= sattr
	};
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_SYMLINK],
		.rpc_argp	= &arg,
	};
	int status = -ENAMETOOLONG;

	dprintk("NFS call  symlink %s\n", dentry->d_name.name);

	if (len > NFS2_MAXPATHLEN)
		goto out;

	fh = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	status = -ENOMEM;
	if (fh == NULL || fattr == NULL)
		goto out_free;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_for_revalidate(dir);

	/*
	 * V2 SYMLINK requests don't return any attributes.  Setting the
	 * filehandle size to zero indicates to nfs_instantiate that it
	 * should fill in the data with a LOOKUP call on the wire.
	 */
	if (status == 0)
		status = nfs_instantiate(dentry, fh, fattr);

out_free:
	nfs_free_fattr(fattr);
	nfs_free_fhandle(fh);
out:
	dprintk("NFS reply symlink: %d\n", status);
	return status;
}