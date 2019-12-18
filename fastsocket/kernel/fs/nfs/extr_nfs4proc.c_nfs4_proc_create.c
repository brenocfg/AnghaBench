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
struct nfs_open_context {struct nfs4_state* state; int /*<<< orphan*/  mode; struct dentry* dentry; struct rpc_cred* cred; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs4_state*) ; 
 int PTR_ERR (struct nfs4_state*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  igrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_close_sync (struct nfs4_state*,int /*<<< orphan*/ ) ; 
 struct nfs4_state* nfs4_do_open (struct inode*,struct dentry*,int /*<<< orphan*/ ,int,struct iattr*,struct rpc_cred*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs4_proc_create(struct inode *dir, struct dentry *dentry, struct iattr *sattr,
                 int flags, struct nfs_open_context *ctx)
{
	struct dentry *de = dentry;
	struct nfs4_state *state;
	struct rpc_cred *cred = NULL;
	fmode_t fmode = 0;
	int status = 0;

	if (ctx != NULL) {
		cred = ctx->cred;
		de = ctx->dentry;
		fmode = ctx->mode;
	}
	state = nfs4_do_open(dir, de, fmode, flags, sattr, cred);
	d_drop(dentry);
	if (IS_ERR(state)) {
		status = PTR_ERR(state);
		goto out;
	}
	d_add(dentry, igrab(state->inode));
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
	if (ctx != NULL)
		ctx->state = state;
	else
		nfs4_close_sync(state, fmode);
out:
	return status;
}