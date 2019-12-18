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
struct nfs_open_context {struct nfs4_state* state; int /*<<< orphan*/  cred; int /*<<< orphan*/  mode; int /*<<< orphan*/  dentry; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;

/* Variables and functions */
 struct inode* ERR_CAST (struct nfs4_state*) ; 
 scalar_t__ IS_ERR (struct nfs4_state*) ; 
 struct inode* igrab (int /*<<< orphan*/ ) ; 
 struct nfs4_state* nfs4_do_open (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *
nfs4_atomic_open(struct inode *dir, struct nfs_open_context *ctx, int open_flags, struct iattr *attr)
{
	struct nfs4_state *state;

	/* Protect against concurrent sillydeletes */
	state = nfs4_do_open(dir, ctx->dentry, ctx->mode, open_flags, attr, ctx->cred);
	if (IS_ERR(state))
		return ERR_CAST(state);
	ctx->state = state;
	return igrab(state->inode);
}