#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfsbuflists {TYPE_2__* lh_first; } ;
typedef  TYPE_3__* nfsnode_t ;
struct TYPE_7__ {int n_bufiterflags; struct nfsbuflists n_cleanblkhd; struct nfsbuflists n_dirtyblkhd; } ;
struct TYPE_5__ {TYPE_2__** le_prev; } ;
struct TYPE_6__ {TYPE_1__ nb_vnbufs; } ;

/* Variables and functions */
 int EINVAL ; 
 int EWOULDBLOCK ; 
 scalar_t__ LIST_EMPTY (struct nfsbuflists*) ; 
 int /*<<< orphan*/  LIST_INIT (struct nfsbuflists*) ; 
 int NBI_DIRTY ; 
 int NBI_ITER ; 
 int NBI_ITERWANT ; 
 int NBI_NOWAIT ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 

int
nfs_buf_iterprepare(nfsnode_t np, struct nfsbuflists *iterheadp, int flags)
{
	struct nfsbuflists *listheadp;

	if (flags & NBI_DIRTY)
		listheadp = &np->n_dirtyblkhd;
	else
		listheadp = &np->n_cleanblkhd;

	if ((flags & NBI_NOWAIT) && (np->n_bufiterflags & NBI_ITER)) {
	        LIST_INIT(iterheadp);
		return(EWOULDBLOCK);
	}

	while (np->n_bufiterflags & NBI_ITER) 	{
	        np->n_bufiterflags |= NBI_ITERWANT;
		msleep(&np->n_bufiterflags, nfs_buf_mutex, 0, "nfs_buf_iterprepare", NULL);
	}
	if (LIST_EMPTY(listheadp)) {
	        LIST_INIT(iterheadp);
		return(EINVAL);
	}
	np->n_bufiterflags |= NBI_ITER;

	iterheadp->lh_first = listheadp->lh_first;
	listheadp->lh_first->nb_vnbufs.le_prev = &iterheadp->lh_first;	
	LIST_INIT(listheadp);

	return(0);
}