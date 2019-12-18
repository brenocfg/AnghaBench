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
struct rpc_cred {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {int /*<<< orphan*/  f_mode; TYPE_1__ f_path; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct rpc_cred*) ; 
 int PTR_ERR (struct rpc_cred*) ; 
 struct nfs_open_context* alloc_nfs_open_context (int /*<<< orphan*/ ,struct rpc_cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_file_set_open_context (struct file*,struct nfs_open_context*) ; 
 int /*<<< orphan*/  nfs_fscache_set_inode_cookie (struct inode*,struct file*) ; 
 int /*<<< orphan*/  put_nfs_open_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rpc_lookup_cred () ; 

int nfs_open(struct inode *inode, struct file *filp)
{
	struct nfs_open_context *ctx;
	struct rpc_cred *cred;

	cred = rpc_lookup_cred();
	if (IS_ERR(cred))
		return PTR_ERR(cred);
	ctx = alloc_nfs_open_context(filp->f_path.dentry, cred, filp->f_mode);
	put_rpccred(cred);
	if (ctx == NULL)
		return -ENOMEM;
	nfs_file_set_open_context(filp, ctx);
	put_nfs_open_context(ctx);
	nfs_fscache_set_inode_cookie(inode, filp);
	return 0;
}