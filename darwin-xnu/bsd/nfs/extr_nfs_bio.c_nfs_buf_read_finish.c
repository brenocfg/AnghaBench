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
struct nfsmount {scalar_t__ nm_vers; } ;
struct nfsbuf {int nb_validend; int nb_endio; scalar_t__ nb_bufsize; int nb_valid; scalar_t__ nb_data; scalar_t__ nb_validoff; int /*<<< orphan*/  nb_flags; TYPE_1__* nb_np; } ;
typedef  scalar_t__ off_t ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_3__ {scalar_t__ n_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NBOFF (struct nfsbuf*) ; 
 int /*<<< orphan*/  NB_ERROR ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 scalar_t__ NFS_VER2 ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  nfs_buf_iodone (struct nfsbuf*) ; 
 int round_page_32 (int) ; 

void
nfs_buf_read_finish(struct nfsbuf *bp)
{
	nfsnode_t np = bp->nb_np;
	struct nfsmount *nmp;

	if (!ISSET(bp->nb_flags, NB_ERROR)) {
		/* update valid range */
		bp->nb_validoff = 0;
		bp->nb_validend = bp->nb_endio;
		if (bp->nb_endio < (int)bp->nb_bufsize) { 
			/*
			 * The read may be short because we have unflushed writes
			 * that are extending the file size and the reads hit the
			 * (old) EOF on the server.  So, just make sure nb_validend
			 * correctly tracks EOF.
			 * Note that the missing data should have already been zeroed
			 * in nfs_buf_read_rpc_finish().
			 */
			off_t boff = NBOFF(bp);
			if ((off_t)np->n_size >= (boff + bp->nb_bufsize))
				bp->nb_validend = bp->nb_bufsize;
			else if ((off_t)np->n_size >= boff)
				bp->nb_validend = np->n_size - boff;
			else
				bp->nb_validend = 0;
		}
		if ((nmp = NFSTONMP(np)) && (nmp->nm_vers == NFS_VER2) &&
		    ((NBOFF(bp) + bp->nb_validend) > 0x100000000LL))
			bp->nb_validend = 0x100000000LL - NBOFF(bp);
		bp->nb_valid = (1 << (round_page_32(bp->nb_validend) / PAGE_SIZE)) - 1;
		if (bp->nb_validend & PAGE_MASK) {
			/* zero-fill remainder of last page */
			bzero(bp->nb_data + bp->nb_validend, PAGE_SIZE - (bp->nb_validend & PAGE_MASK));
		}
	}
	nfs_buf_iodone(bp);
}