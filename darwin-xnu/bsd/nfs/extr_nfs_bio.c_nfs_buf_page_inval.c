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
typedef  int /*<<< orphan*/  vnode_t ;
struct nfsmount {int nm_biosize; } ;
struct nfsbuf {scalar_t__ nb_dirtyoff; scalar_t__ nb_dirtyend; int /*<<< orphan*/  nb_lflags; int /*<<< orphan*/  nb_flags; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  daddr64_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  FSDBG (int,struct nfsbuf*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBL_BUSY ; 
 int NBOFF (struct nfsbuf*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTONFS (int /*<<< orphan*/ ) ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_free ; 
 int /*<<< orphan*/  nfs_buf_delwri_push (int) ; 
 struct nfsbuf* nfs_buf_incore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_remfree (struct nfsbuf*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfsbufdelwri ; 
 int /*<<< orphan*/  nfsbufdelwricnt ; 

int
nfs_buf_page_inval(vnode_t vp, off_t offset)
{
	struct nfsmount *nmp = VTONMP(vp);
	struct nfsbuf *bp;
	int error = 0;

	if (nfs_mount_gone(nmp))
		return (ENXIO);

	lck_mtx_lock(nfs_buf_mutex);
	bp = nfs_buf_incore(VTONFS(vp), (daddr64_t)(offset / nmp->nm_biosize));
	if (!bp)
		goto out;
	FSDBG(325, bp, bp->nb_flags, bp->nb_dirtyoff, bp->nb_dirtyend);
	if (ISSET(bp->nb_lflags, NBL_BUSY)) {
		error = EBUSY;
		goto out;
	}
	/*
	 * If there's a dirty range in the buffer, check to
	 * see if this page intersects with the dirty range.
	 * If it does, we can't let the pager drop the page.
	 */
	if (bp->nb_dirtyend > 0) {
		int start = offset - NBOFF(bp);
		if ((bp->nb_dirtyend > start) &&
		    (bp->nb_dirtyoff < (start + PAGE_SIZE))) {
			/*
			 * Before returning the bad news, move the
			 * buffer to the start of the delwri list and
			 * give the list a push to try to flush the
			 * buffer out.
			 */
			error = EBUSY;
			nfs_buf_remfree(bp);
			TAILQ_INSERT_HEAD(&nfsbufdelwri, bp, nb_free);
			nfsbufdelwricnt++;
			nfs_buf_delwri_push(1);
		}
	}
out:
	lck_mtx_unlock(nfs_buf_mutex);
	return (error);
}