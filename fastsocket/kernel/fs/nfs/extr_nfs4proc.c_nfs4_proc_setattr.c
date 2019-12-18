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
struct rpc_cred {int dummy; } ;
struct nfs_open_context {struct nfs4_state* state; struct rpc_cred* cred; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_state {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_file; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_FILE ; 
 int ATTR_MTIME ; 
 int ATTR_OPEN ; 
 int nfs4_do_setattr (struct inode*,struct rpc_cred*,struct nfs_fattr*,struct iattr*,struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 
 struct nfs_open_context* nfs_file_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_setattr_update_inode (struct inode*,struct iattr*) ; 
 scalar_t__ pnfs_ld_layoutret_on_setattr (struct inode*) ; 
 int /*<<< orphan*/  pnfs_return_layout (struct inode*) ; 

__attribute__((used)) static int
nfs4_proc_setattr(struct dentry *dentry, struct nfs_fattr *fattr,
		  struct iattr *sattr)
{
	struct inode *inode = dentry->d_inode;
	struct rpc_cred *cred = NULL;
	struct nfs4_state *state = NULL;
	int status;

	if (pnfs_ld_layoutret_on_setattr(inode))
		pnfs_return_layout(inode);

	nfs_fattr_init(fattr);
	
	/* Deal with open(O_TRUNC) */
	if (sattr->ia_valid & ATTR_OPEN)
		sattr->ia_valid &= ~(ATTR_MTIME|ATTR_CTIME);

	/* Optimization: if the end result is no change, don't RPC */
	if ((sattr->ia_valid & ~(ATTR_FILE|ATTR_OPEN)) == 0)
		return 0;

	/* Search for an existing open(O_WRITE) file */
	if (sattr->ia_valid & ATTR_FILE) {
		struct nfs_open_context *ctx;

		ctx = nfs_file_open_context(sattr->ia_file);
		if (ctx) {
			cred = ctx->cred;
			state = ctx->state;
		}
	}

	status = nfs4_do_setattr(inode, cred, fattr, sattr, state);
	if (status == 0)
		nfs_setattr_update_inode(inode, sattr);
	return status;
}