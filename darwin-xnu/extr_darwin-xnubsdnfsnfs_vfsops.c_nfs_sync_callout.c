#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
struct nfs_sync_cargs {int error; int /*<<< orphan*/  ctx; int /*<<< orphan*/  waitfor; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_4__ {int n_flag; scalar_t__ n_wrbusy; int n_bflag; int /*<<< orphan*/  n_dirtyblkhd; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int NBFLUSHINPROG ; 
 int NBINVALINPROG ; 
 int NREVOKE ; 
 int /*<<< orphan*/  REVOKEALL ; 
 int VNODE_RETURNED ; 
 TYPE_1__* VTONFS (int /*<<< orphan*/ ) ; 
 int nfs_flush (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_revoke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_sync_callout(vnode_t vp, void *arg)
{
	struct nfs_sync_cargs *cargs = (struct nfs_sync_cargs*)arg;
	nfsnode_t np = VTONFS(vp);
	int error;

	if (np->n_flag & NREVOKE) {
		vn_revoke(vp, REVOKEALL, cargs->ctx);
		return (VNODE_RETURNED);
	}

	if (LIST_EMPTY(&np->n_dirtyblkhd))
		return (VNODE_RETURNED);
	if (np->n_wrbusy > 0)
		return (VNODE_RETURNED);
	if (np->n_bflag & (NBFLUSHINPROG|NBINVALINPROG))
		return (VNODE_RETURNED);

	error = nfs_flush(np, cargs->waitfor, vfs_context_thread(cargs->ctx), 0);
	if (error)
		cargs->error = error;

	return (VNODE_RETURNED);
}