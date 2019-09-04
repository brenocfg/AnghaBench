#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsbuflists {int dummy; } ;
struct nfsbuf {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_3__ {int n_bufiterflags; struct nfsbuflists n_cleanblkhd; struct nfsbuflists n_dirtyblkhd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (struct nfsbuflists*) ; 
 struct nfsbuf* LIST_FIRST (struct nfsbuflists*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct nfsbuflists*,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int NBI_DIRTY ; 
 int NBI_ITER ; 
 int NBI_ITERWANT ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
nfs_buf_itercomplete(nfsnode_t np, struct nfsbuflists *iterheadp, int flags)
{
	struct nfsbuflists * listheadp;
	struct nfsbuf *bp;

	if (flags & NBI_DIRTY)
		listheadp = &np->n_dirtyblkhd;
	else
		listheadp = &np->n_cleanblkhd;

	while (!LIST_EMPTY(iterheadp)) {
		bp = LIST_FIRST(iterheadp);
		LIST_REMOVE(bp, nb_vnbufs);
		LIST_INSERT_HEAD(listheadp, bp, nb_vnbufs);
	}

	np->n_bufiterflags &= ~NBI_ITER;
	if (np->n_bufiterflags & NBI_ITERWANT) {
		np->n_bufiterflags &= ~NBI_ITERWANT;
		wakeup(&np->n_bufiterflags);
	}
}