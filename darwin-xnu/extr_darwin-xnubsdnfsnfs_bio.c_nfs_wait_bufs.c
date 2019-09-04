#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfsbuflists {int dummy; } ;
struct nfsbuf {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  n_dirtyblkhd; int /*<<< orphan*/  n_cleanblkhd; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct nfsbuf* LIST_FIRST (struct nfsbuflists*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBI_CLEAN ; 
 int /*<<< orphan*/  NBI_DIRTY ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 int nfs_buf_acquire (struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_drop (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_itercomplete (TYPE_1__*,struct nfsbuflists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_iterprepare (TYPE_1__*,struct nfsbuflists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_refget (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_refrele (struct nfsbuf*) ; 

void
nfs_wait_bufs(nfsnode_t np)
{
	struct nfsbuf *bp;
	struct nfsbuflists blist;
	int error = 0;

	lck_mtx_lock(nfs_buf_mutex);
	if (!nfs_buf_iterprepare(np, &blist, NBI_CLEAN)) {
		while ((bp = LIST_FIRST(&blist))) {
			LIST_REMOVE(bp, nb_vnbufs);
			LIST_INSERT_HEAD(&np->n_cleanblkhd, bp, nb_vnbufs);
			nfs_buf_refget(bp);
			while ((error = nfs_buf_acquire(bp, 0, 0, 0))) {
				if (error != EAGAIN) {
					nfs_buf_refrele(bp);
					nfs_buf_itercomplete(np, &blist, NBI_CLEAN);
					lck_mtx_unlock(nfs_buf_mutex);
					return;
				}
			}
			nfs_buf_refrele(bp);
			nfs_buf_drop(bp);
		}
		nfs_buf_itercomplete(np, &blist, NBI_CLEAN);
	}
	if (!nfs_buf_iterprepare(np, &blist, NBI_DIRTY)) {
		while ((bp = LIST_FIRST(&blist))) {
			LIST_REMOVE(bp, nb_vnbufs);
			LIST_INSERT_HEAD(&np->n_dirtyblkhd, bp, nb_vnbufs);
			nfs_buf_refget(bp);
			while ((error = nfs_buf_acquire(bp, 0, 0, 0))) {
				if (error != EAGAIN) {
					nfs_buf_refrele(bp);
					nfs_buf_itercomplete(np, &blist, NBI_DIRTY);
					lck_mtx_unlock(nfs_buf_mutex);
					return;
				}
			}
			nfs_buf_refrele(bp);
			nfs_buf_drop(bp);
		}
		nfs_buf_itercomplete(np, &blist, NBI_DIRTY);
	}
	lck_mtx_unlock(nfs_buf_mutex);
}