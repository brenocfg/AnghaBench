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
struct nfsbuf {int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_np; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NB_ASYNC ; 
 int /*<<< orphan*/  NB_NEEDCOMMIT ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfsbuf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_free ; 
 int nfs_buf_acquire (struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_check_write_verifier (int /*<<< orphan*/ ,struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_drop (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_refget (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_refrele (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_remfree (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_write (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_flushcommits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsbufdelwri ; 
 int /*<<< orphan*/  nfsbufdelwricnt ; 

void
nfs_buf_delwri_service(void)
{
	struct nfsbuf *bp;
	nfsnode_t np;
	int error, i = 0;

	while (i < 8 && (bp = TAILQ_FIRST(&nfsbufdelwri)) != NULL) {
		np = bp->nb_np;
		nfs_buf_remfree(bp);
		nfs_buf_refget(bp);
		while ((error = nfs_buf_acquire(bp, 0, 0, 0)) == EAGAIN);
		nfs_buf_refrele(bp);
		if (error)
			break;
		if (!bp->nb_np) {
			/* buffer is no longer valid */
			nfs_buf_drop(bp);
			continue;
		}
		if (ISSET(bp->nb_flags, NB_NEEDCOMMIT))
			nfs_buf_check_write_verifier(np, bp);
		if (ISSET(bp->nb_flags, NB_NEEDCOMMIT)) {
			/* put buffer at end of delwri list */
			TAILQ_INSERT_TAIL(&nfsbufdelwri, bp, nb_free);
			nfsbufdelwricnt++;
			nfs_buf_drop(bp);
			lck_mtx_unlock(nfs_buf_mutex);
			nfs_flushcommits(np, 1);
		} else {
			SET(bp->nb_flags, NB_ASYNC);
			lck_mtx_unlock(nfs_buf_mutex);
			nfs_buf_write(bp);
		}
		i++;
		lck_mtx_lock(nfs_buf_mutex);
	}
}