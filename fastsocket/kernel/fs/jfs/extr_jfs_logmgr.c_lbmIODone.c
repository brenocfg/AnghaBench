#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lbuf {int l_flag; int l_pn; int /*<<< orphan*/  l_ioevent; struct lbuf* l_wqnext; scalar_t__ l_ceor; struct jfs_log* l_log; } ;
struct jfs_log {struct lbuf* wqueue; scalar_t__ clsn; } ;
struct bio {int /*<<< orphan*/  bi_flags; struct lbuf* bi_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  pagedone; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 int L2LOGPSIZE ; 
 int /*<<< orphan*/  LCACHE_LOCK (unsigned long) ; 
 int /*<<< orphan*/  LCACHE_UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  LCACHE_WAKEUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct lbuf*,int) ; 
 int lbmDIRECT ; 
 int lbmDONE ; 
 int lbmERROR ; 
 int lbmFREE ; 
 int lbmGC ; 
 int lbmREAD ; 
 int lbmRELEASE ; 
 int /*<<< orphan*/  lbmRedrive (struct lbuf*) ; 
 int lbmSYNC ; 
 int lbmWRITE ; 
 int /*<<< orphan*/  lbmfree (struct lbuf*) ; 
 int /*<<< orphan*/  lmPostGC (struct lbuf*) ; 
 TYPE_1__ lmStat ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lbmIODone(struct bio *bio, int error)
{
	struct lbuf *bp = bio->bi_private;
	struct lbuf *nextbp, *tail;
	struct jfs_log *log;
	unsigned long flags;

	/*
	 * get back jfs buffer bound to the i/o buffer
	 */
	jfs_info("lbmIODone: bp:0x%p flag:0x%x", bp, bp->l_flag);

	LCACHE_LOCK(flags);		/* disable+lock */

	bp->l_flag |= lbmDONE;

	if (!test_bit(BIO_UPTODATE, &bio->bi_flags)) {
		bp->l_flag |= lbmERROR;

		jfs_err("lbmIODone: I/O error in JFS log");
	}

	bio_put(bio);

	/*
	 *	pagein completion
	 */
	if (bp->l_flag & lbmREAD) {
		bp->l_flag &= ~lbmREAD;

		LCACHE_UNLOCK(flags);	/* unlock+enable */

		/* wakeup I/O initiator */
		LCACHE_WAKEUP(&bp->l_ioevent);

		return;
	}

	/*
	 *	pageout completion
	 *
	 * the bp at the head of write queue has completed pageout.
	 *
	 * if single-commit/full-page pageout, remove the current buffer
	 * from head of pageout queue, and redrive pageout with
	 * the new buffer at head of pageout queue;
	 * otherwise, the partial-page pageout buffer stays at
	 * the head of pageout queue to be redriven for pageout
	 * by lmGroupCommit() until full-page pageout is completed.
	 */
	bp->l_flag &= ~lbmWRITE;
	INCREMENT(lmStat.pagedone);

	/* update committed lsn */
	log = bp->l_log;
	log->clsn = (bp->l_pn << L2LOGPSIZE) + bp->l_ceor;

	if (bp->l_flag & lbmDIRECT) {
		LCACHE_WAKEUP(&bp->l_ioevent);
		LCACHE_UNLOCK(flags);
		return;
	}

	tail = log->wqueue;

	/* single element queue */
	if (bp == tail) {
		/* remove head buffer of full-page pageout
		 * from log device write queue
		 */
		if (bp->l_flag & lbmRELEASE) {
			log->wqueue = NULL;
			bp->l_wqnext = NULL;
		}
	}
	/* multi element queue */
	else {
		/* remove head buffer of full-page pageout
		 * from log device write queue
		 */
		if (bp->l_flag & lbmRELEASE) {
			nextbp = tail->l_wqnext = bp->l_wqnext;
			bp->l_wqnext = NULL;

			/*
			 * redrive pageout of next page at head of write queue:
			 * redrive next page without any bound tblk
			 * (i.e., page w/o any COMMIT records), or
			 * first page of new group commit which has been
			 * queued after current page (subsequent pageout
			 * is performed synchronously, except page without
			 * any COMMITs) by lmGroupCommit() as indicated
			 * by lbmWRITE flag;
			 */
			if (nextbp->l_flag & lbmWRITE) {
				/*
				 * We can't do the I/O at interrupt time.
				 * The jfsIO thread can do it
				 */
				lbmRedrive(nextbp);
			}
		}
	}

	/*
	 *	synchronous pageout:
	 *
	 * buffer has not necessarily been removed from write queue
	 * (e.g., synchronous write of partial-page with COMMIT):
	 * leave buffer for i/o initiator to dispose
	 */
	if (bp->l_flag & lbmSYNC) {
		LCACHE_UNLOCK(flags);	/* unlock+enable */

		/* wakeup I/O initiator */
		LCACHE_WAKEUP(&bp->l_ioevent);
	}

	/*
	 *	Group Commit pageout:
	 */
	else if (bp->l_flag & lbmGC) {
		LCACHE_UNLOCK(flags);
		lmPostGC(bp);
	}

	/*
	 *	asynchronous pageout:
	 *
	 * buffer must have been removed from write queue:
	 * insert buffer at head of freelist where it can be recycled
	 */
	else {
		assert(bp->l_flag & lbmRELEASE);
		assert(bp->l_flag & lbmFREE);
		lbmfree(bp);

		LCACHE_UNLOCK(flags);	/* unlock+enable */
	}
}