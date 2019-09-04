#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ le_next; } ;
struct nfsbuf {int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_error; TYPE_1__ nb_vnbufs; int /*<<< orphan*/  nb_dirty; int /*<<< orphan*/  nb_dirtyend; int /*<<< orphan*/  nb_dirtyoff; TYPE_2__* nb_np; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_7__ {int /*<<< orphan*/  n_flag; int /*<<< orphan*/  n_dirtyblkhd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSDBG (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_ASYNC ; 
 int /*<<< orphan*/  NB_DELWRI ; 
 int /*<<< orphan*/  NB_DONE ; 
 int /*<<< orphan*/  NFSBUFCNTCHK () ; 
 scalar_t__ NFSNOLIST ; 
 int /*<<< orphan*/  NFSTOV (TYPE_2__*) ; 
 scalar_t__ NFS_A_LOT_OF_DELAYED_WRITES ; 
 int /*<<< orphan*/  NMODIFIED ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNODE_ASYNC_THROTTLE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_vnbufs ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_release (struct nfsbuf*,int) ; 
 int /*<<< orphan*/  nfs_buf_write (struct nfsbuf*) ; 
 scalar_t__ nfs_nbdwrite ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vnode_waitforwrites (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
nfs_buf_write_delayed(struct nfsbuf *bp)
{
	nfsnode_t np = bp->nb_np;

	FSDBG_TOP(551, bp, NBOFF(bp), bp->nb_flags, 0);
	FSDBG(551, bp, bp->nb_dirtyoff, bp->nb_dirtyend, bp->nb_dirty);

	/*
	 * If the block hasn't been seen before:
	 *	(1) Mark it as having been seen,
	 *	(2) Make sure it's on its node's correct block list,
	 */
	if (!ISSET(bp->nb_flags, NB_DELWRI)) {
		SET(bp->nb_flags, NB_DELWRI);
		/* move to dirty list */
		lck_mtx_lock(nfs_buf_mutex);
		nfs_nbdwrite++;
		NFSBUFCNTCHK();
		if (bp->nb_vnbufs.le_next != NFSNOLIST)
			LIST_REMOVE(bp, nb_vnbufs);
		LIST_INSERT_HEAD(&np->n_dirtyblkhd, bp, nb_vnbufs);
		lck_mtx_unlock(nfs_buf_mutex);
	}

	/*
	 * If the vnode has "too many" write operations in progress
	 * wait for them to finish the IO
	 */
	vnode_waitforwrites(NFSTOV(np), VNODE_ASYNC_THROTTLE, 0, 0, "nfs_buf_write_delayed");

	/* the file is in a modified state, so make sure the flag's set */
	nfs_node_lock_force(np);
	np->n_flag |= NMODIFIED;
	nfs_node_unlock(np);

	/*
	 * If we have too many delayed write buffers,
	 * just fall back to doing the async write.
	 */
	if (nfs_nbdwrite < 0)
		panic("nfs_buf_write_delayed: Negative nfs_nbdwrite");
	if (nfs_nbdwrite > NFS_A_LOT_OF_DELAYED_WRITES) {
		/* issue async write */
		SET(bp->nb_flags, NB_ASYNC);
		nfs_buf_write(bp);
		FSDBG_BOT(551, bp, NBOFF(bp), bp->nb_flags, bp->nb_error);
		return;
	}

	/* Otherwise, the "write" is done, so mark and release the buffer. */
	SET(bp->nb_flags, NB_DONE);
	nfs_buf_release(bp, 1);
	FSDBG_BOT(551, bp, NBOFF(bp), bp->nb_flags, 0);
	return;
}