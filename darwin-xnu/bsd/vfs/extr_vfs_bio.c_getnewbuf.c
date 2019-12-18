#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
struct buf {int b_whichq; int b_timestamp; int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_lflags; } ;
typedef  struct buf* buf_t ;
struct TYPE_5__ {struct buf* tqh_first; } ;
struct TYPE_4__ {int /*<<< orphan*/  bufs_sleeps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLISTNONE (struct buf*) ; 
 int /*<<< orphan*/  BL_BUSY ; 
 int BQUEUES ; 
 size_t BQ_AGE ; 
 int BQ_EMPTY ; 
 int BQ_LAUNDRY ; 
 int BQ_LOCKED ; 
 size_t BQ_LRU ; 
 size_t BQ_META ; 
 int /*<<< orphan*/  B_HDRALLOC ; 
 int /*<<< orphan*/  B_LOCKED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NSEC_PER_USEC ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int age_is_stale ; 
 scalar_t__ bcleanbuf (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binshash (struct buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binsheadfree (struct buf*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  buf_hdr_count ; 
 int /*<<< orphan*/  buf_hdr_zone ; 
 int /*<<< orphan*/  buf_mtxp ; 
 void* buf_timestamp () ; 
 int /*<<< orphan*/  bufhdrinit (struct buf*) ; 
 TYPE_2__* bufqueues ; 
 TYPE_1__ bufstats ; 
 int /*<<< orphan*/  invalhash ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int lru_is_stale ; 
 scalar_t__ max_nbuf_headers ; 
 int meta_is_stale ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ ,int,char*,struct timespec*) ; 
 scalar_t__ nbuf_headers ; 
 int needbuffer ; 
 int /*<<< orphan*/  panic (char*,struct buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static buf_t
getnewbuf(int slpflag, int slptimeo, int * queue)
{
	buf_t	bp;
	buf_t	lru_bp;
	buf_t	age_bp;
	buf_t	meta_bp;
	int	age_time, lru_time, bp_time, meta_time;
	int	req = *queue;	/* save it for restarts */
	struct timespec ts;

start:
	/*
	 * invalid request gets empty queue
	 */
	if ((*queue >= BQUEUES) || (*queue < 0)
		|| (*queue == BQ_LAUNDRY) || (*queue == BQ_LOCKED))
		*queue = BQ_EMPTY;


	if (*queue == BQ_EMPTY && (bp = bufqueues[*queue].tqh_first))
	        goto found;

	/*
	 * need to grow number of bufs, add another one rather than recycling
	 */
	if (nbuf_headers < max_nbuf_headers) {
		/*
		 * Increment  count now as lock 
		 * is dropped for allocation.
		 * That avoids over commits
		 */
		nbuf_headers++;
		goto add_newbufs;
	}
	/* Try for the requested queue first */
	bp = bufqueues[*queue].tqh_first;
	if (bp)
	        goto found;

	/* Unable to use requested queue */
	age_bp = bufqueues[BQ_AGE].tqh_first;
	lru_bp = bufqueues[BQ_LRU].tqh_first;
	meta_bp = bufqueues[BQ_META].tqh_first;

	if (!age_bp && !lru_bp && !meta_bp) {
		/*
		 * Unavailble on AGE or LRU or META queues
		 * Try the empty list first
		 */
		bp = bufqueues[BQ_EMPTY].tqh_first;
		if (bp) {
			*queue = BQ_EMPTY;
			goto found;
		}
		/*
		 * We have seen is this is hard to trigger.
		 * This is an overcommit of nbufs but needed 
		 * in some scenarios with diskiamges
		 */

add_newbufs:
		lck_mtx_unlock(buf_mtxp);

		/* Create a new temporary buffer header */
		bp = (struct buf *)zalloc(buf_hdr_zone);
		
		if (bp) {
			bufhdrinit(bp);
			bp->b_whichq = BQ_EMPTY;
			bp->b_timestamp = buf_timestamp();
			BLISTNONE(bp);
			SET(bp->b_flags, B_HDRALLOC);
			*queue = BQ_EMPTY;
		}
		lck_mtx_lock_spin(buf_mtxp);

		if (bp) {
			binshash(bp, &invalhash);
			binsheadfree(bp, &bufqueues[BQ_EMPTY], BQ_EMPTY);
			buf_hdr_count++;
			goto found;
		}
		/* subtract already accounted bufcount */
		nbuf_headers--;

		bufstats.bufs_sleeps++;

		/* wait for a free buffer of any kind */
		needbuffer = 1;
		/* hz value is 100 */
		ts.tv_sec = (slptimeo/1000);
		/* the hz value is 100; which leads to 10ms */
		ts.tv_nsec = (slptimeo % 1000) * NSEC_PER_USEC * 1000 * 10;

		msleep(&needbuffer, buf_mtxp, slpflag | PDROP | (PRIBIO+1), "getnewbuf", &ts);
		return (NULL);
	}

	/* Buffer available either on AGE or LRU or META */
	bp = NULL;
	*queue = -1;

	/* Buffer available either on AGE or LRU */
	if (!age_bp) {
		bp = lru_bp;
		*queue = BQ_LRU;
	} else if (!lru_bp) {
		bp = age_bp;
		*queue = BQ_AGE;
	} else { /* buffer available on both AGE and LRU */
		int		t = buf_timestamp();

		age_time = t - age_bp->b_timestamp;
		lru_time = t - lru_bp->b_timestamp;
		if ((age_time < 0) || (lru_time < 0)) { /* time set backwards */
			bp = age_bp;
			*queue = BQ_AGE;
			/*
			 * we should probably re-timestamp eveything in the
			 * queues at this point with the current time
			 */
		} else {
			if ((lru_time >= lru_is_stale) && (age_time < age_is_stale)) {
				bp = lru_bp;
				*queue = BQ_LRU;
			} else {
				bp = age_bp;
				*queue = BQ_AGE;
			}
		}
	}

	if (!bp) { /* Neither on AGE nor on LRU */
		bp = meta_bp;
		*queue = BQ_META;
	}  else if (meta_bp) {
		int		t = buf_timestamp();

		bp_time = t - bp->b_timestamp;
		meta_time = t - meta_bp->b_timestamp;

		if (!(bp_time < 0) && !(meta_time < 0)) {
			/* time not set backwards */
			int bp_is_stale;
			bp_is_stale = (*queue == BQ_LRU) ? 
					lru_is_stale : age_is_stale;

			if ((meta_time >= meta_is_stale) && 
					(bp_time < bp_is_stale)) {
				bp = meta_bp;
				*queue = BQ_META;
			}
		}
	}
found:
	if (ISSET(bp->b_flags, B_LOCKED) || ISSET(bp->b_lflags, BL_BUSY))
	        panic("getnewbuf: bp @ %p is LOCKED or BUSY! (flags 0x%x)\n", bp, bp->b_flags);

	/* Clean it */
	if (bcleanbuf(bp, FALSE)) {
		/*
		 * moved to the laundry thread, buffer not ready
		 */
		*queue = req;
		goto start;
	}
	return (bp); 
}