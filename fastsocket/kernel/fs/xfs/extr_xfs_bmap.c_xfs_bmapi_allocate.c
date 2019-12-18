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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_extnum_t ;
struct xfs_btree_cur {int dummy; } ;
struct xfs_bmap_free {int dummy; } ;
struct xfs_bmalloca {int /*<<< orphan*/  stack_switch; } ;
struct xfs_bmalloc_work {int flags; int* nallocs; int* logflags; int result; int /*<<< orphan*/  work; struct xfs_bmap_free* flist; int /*<<< orphan*/ * firstblock; struct xfs_btree_cur** cur; int /*<<< orphan*/ * lastx; struct xfs_bmalloca* bma; int /*<<< orphan*/ * done; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __xfs_bmapi_allocate (struct xfs_bmalloca*,int /*<<< orphan*/ *,struct xfs_btree_cur**,int /*<<< orphan*/ *,struct xfs_bmap_free*,int,int*,int*) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_alloc_wq ; 
 int /*<<< orphan*/  xfs_bmapi_allocate_worker ; 

int
xfs_bmapi_allocate(
	struct xfs_bmalloca	*bma,
	xfs_extnum_t		*lastx,
	struct xfs_btree_cur	**cur,
	xfs_fsblock_t		*firstblock,
	struct xfs_bmap_free	*flist,
	int			flags,
	int			*nallocs,
	int			*logflags)
{
	DECLARE_COMPLETION_ONSTACK(done);
	struct xfs_bmalloc_work	args;

	if (!bma->stack_switch)
		return __xfs_bmapi_allocate(bma, lastx, cur, firstblock, flist,
					    flags, nallocs, logflags);

	args.done = &done;
	args.bma = bma;
	args.lastx = lastx;
	args.cur = cur;
	args.firstblock = firstblock;
	args.flist = flist;
	args.flags = flags;
	args.nallocs = nallocs;
	args.logflags = logflags;
	INIT_WORK(&args.work, xfs_bmapi_allocate_worker);
	queue_work(xfs_alloc_wq, &args.work);
	wait_for_completion(&done);
	return args.result;
}