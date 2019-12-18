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
struct rpc_message {struct rpc_cred* rpc_cred; struct nfs_readdirargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct page {int dummy; } ;
struct nfs_readdirargs {unsigned int count; struct page** pages; scalar_t__ cookie; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 size_t NFSPROC_READDIR ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  nfs_invalidate_atime (struct inode*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_readdir(struct dentry *dentry, struct rpc_cred *cred,
		 u64 cookie, struct page **pages, unsigned int count, int plus)
{
	struct inode		*dir = dentry->d_inode;
	struct nfs_readdirargs	arg = {
		.fh		= NFS_FH(dir),
		.cookie		= cookie,
		.count		= count,
		.pages		= pages,
	};
	struct rpc_message	msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_READDIR],
		.rpc_argp	= &arg,
		.rpc_cred	= cred,
	};
	int			status;

	dprintk("NFS call  readdir %d\n", (unsigned int)cookie);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);

	nfs_invalidate_atime(dir);

	dprintk("NFS reply readdir: %d\n", status);
	return status;
}