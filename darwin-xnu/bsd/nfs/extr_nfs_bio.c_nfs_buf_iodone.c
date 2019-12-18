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
struct nfsbuf {int /*<<< orphan*/  nb_error; int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_lflags; TYPE_1__* nb_np; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_numoutput; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBL_WANTED ; 
 int /*<<< orphan*/  NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_ASYNC ; 
 int /*<<< orphan*/  NB_DONE ; 
 int /*<<< orphan*/  NB_READ ; 
 int /*<<< orphan*/  NB_WRITEINPROG ; 
 int /*<<< orphan*/  NFSTOV (TYPE_1__*) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_writedone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct nfsbuf*) ; 

void
nfs_buf_iodone(struct nfsbuf *bp)
{

	FSDBG_TOP(550, bp, NBOFF(bp), bp->nb_flags, bp->nb_error);

	if (ISSET(bp->nb_flags, NB_DONE))
		panic("nfs_buf_iodone already");

	if (!ISSET(bp->nb_flags, NB_READ)) {
		CLR(bp->nb_flags, NB_WRITEINPROG);
		/*
		 * vnode_writedone() takes care of waking up
		 * any throttled write operations
		 */
		vnode_writedone(NFSTOV(bp->nb_np));
		nfs_node_lock_force(bp->nb_np);
		bp->nb_np->n_numoutput--;
		nfs_node_unlock(bp->nb_np);
	}
	if (ISSET(bp->nb_flags, NB_ASYNC)) {	/* if async, release it */
		SET(bp->nb_flags, NB_DONE);		/* note that it's done */
		nfs_buf_release(bp, 1);
	} else {		                        /* or just wakeup the buffer */	
	        lck_mtx_lock(nfs_buf_mutex);
		SET(bp->nb_flags, NB_DONE);		/* note that it's done */
		CLR(bp->nb_lflags, NBL_WANTED);
	        lck_mtx_unlock(nfs_buf_mutex);
		wakeup(bp);
	}

	FSDBG_BOT(550, bp, NBOFF(bp), bp->nb_flags, bp->nb_error);
}