#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs_seqid {int dummy; } ;
struct nfs_open_context {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * stateid; struct nfs_seqid* seqid; int /*<<< orphan*/ * fl; int /*<<< orphan*/  fh; } ;
struct TYPE_5__ {struct nfs_seqid* seqid; } ;
struct nfs4_unlockdata {int /*<<< orphan*/  server; int /*<<< orphan*/  fl; int /*<<< orphan*/  ctx; struct nfs4_lock_state* lsp; TYPE_3__ arg; TYPE_2__ res; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_count; int /*<<< orphan*/  ls_stateid; TYPE_1__* ls_state; } ;
struct inode {int dummy; } ;
struct file_lock {int dummy; } ;
struct TYPE_4__ {struct inode* inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_nfs_open_context (struct nfs_open_context*) ; 
 struct nfs4_unlockdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct file_lock*,int) ; 

__attribute__((used)) static struct nfs4_unlockdata *nfs4_alloc_unlockdata(struct file_lock *fl,
		struct nfs_open_context *ctx,
		struct nfs4_lock_state *lsp,
		struct nfs_seqid *seqid)
{
	struct nfs4_unlockdata *p;
	struct inode *inode = lsp->ls_state->inode;

	p = kzalloc(sizeof(*p), GFP_NOFS);
	if (p == NULL)
		return NULL;
	p->arg.fh = NFS_FH(inode);
	p->arg.fl = &p->fl;
	p->arg.seqid = seqid;
	p->res.seqid = seqid;
	p->arg.stateid = &lsp->ls_stateid;
	p->lsp = lsp;
	atomic_inc(&lsp->ls_count);
	/* Ensure we don't close file until we're done freeing locks! */
	p->ctx = get_nfs_open_context(ctx);
	memcpy(&p->fl, fl, sizeof(p->fl));
	p->server = NFS_SERVER(inode);
	return p;
}