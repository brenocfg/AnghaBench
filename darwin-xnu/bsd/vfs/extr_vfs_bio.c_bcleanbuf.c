#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct bufattr {int dummy; } ;
typedef  TYPE_1__* buf_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_12__ {int b_tag; int b_flags; int b_lflags; size_t b_whichq; uintptr_t b_datap; int /*<<< orphan*/  b_attr; scalar_t__ b_validend; scalar_t__ b_validoff; scalar_t__ b_dirtyend; scalar_t__ b_dirtyoff; scalar_t__ b_bcount; scalar_t__ b_resid; scalar_t__ b_error; int /*<<< orphan*/ * b_iodone; scalar_t__ b_lblkno; scalar_t__ b_blkno; int /*<<< orphan*/  b_dev; scalar_t__ b_redundancy_flags; void* b_owner; void* b_fsprivate; void* b_upl; scalar_t__ b_bufsize; scalar_t__ b_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLISTNONE (TYPE_1__*) ; 
 int BL_BUSY ; 
 int BL_WANTDEALLOC ; 
 size_t BQ_EMPTY ; 
 size_t BQ_LAUNDRY ; 
 int B_AGE ; 
 int B_ASYNC ; 
 int B_DELWRI ; 
 int B_FUA ; 
 int B_HDRALLOC ; 
 int B_LOCKED ; 
 int B_META ; 
 int B_NOCACHE ; 
 int B_ZALLOC ; 
 int /*<<< orphan*/  CLR (int,int) ; 
 scalar_t__ ISSET (int,int) ; 
 int /*<<< orphan*/  NODEV ; 
 int /*<<< orphan*/  SET (int,int) ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  TR_BRELSE ; 
 int /*<<< orphan*/  binshash (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binsheadfree (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bmovelaundry (TYPE_1__*) ; 
 int /*<<< orphan*/  brelvp_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  bremfree_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  bremhash (TYPE_1__*) ; 
 int /*<<< orphan*/  buf_busycount ; 
 int /*<<< orphan*/  buf_free_meta_store (TYPE_1__*) ; 
 int /*<<< orphan*/  buf_mtxp ; 
 int /*<<< orphan*/  buf_release_credentials (TYPE_1__*) ; 
 int /*<<< orphan*/ * bufqueues ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 void* current_thread () ; 
 int /*<<< orphan*/  invalhash ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
bcleanbuf(buf_t bp, boolean_t discard)
{
	/* Remove from the queue */
	bremfree_locked(bp);

#ifdef JOE_DEBUG
	bp->b_owner = current_thread();
	bp->b_tag   = 2;
#endif
	/*
	 * If buffer was a delayed write, start the IO by queuing
	 * it on the LAUNDRY queue, and return 1
	 */
	if (ISSET(bp->b_flags, B_DELWRI)) {
		if (discard) {
			SET(bp->b_lflags, BL_WANTDEALLOC);
		}

		bmovelaundry(bp);

		lck_mtx_unlock(buf_mtxp);

		wakeup(&bufqueues[BQ_LAUNDRY]);
		/*
		 * and give it a chance to run
		 */
		(void)thread_block(THREAD_CONTINUE_NULL);

		lck_mtx_lock_spin(buf_mtxp);

		return (1);
	}
#ifdef JOE_DEBUG
	bp->b_owner = current_thread();
	bp->b_tag   = 8;
#endif
	/*
	 * Buffer is no longer on any free list... we own it
	 */
	SET(bp->b_lflags, BL_BUSY);
	buf_busycount++;
	
	bremhash(bp);

	/*
	 * disassociate us from our vnode, if we had one...
	 */
	if (bp->b_vp)
		brelvp_locked(bp);

	lck_mtx_unlock(buf_mtxp);

	BLISTNONE(bp);

	if (ISSET(bp->b_flags, B_META))
		buf_free_meta_store(bp);

	trace(TR_BRELSE, pack(bp->b_vp, bp->b_bufsize), bp->b_lblkno);

	buf_release_credentials(bp);
	
	/* If discarding, just move to the empty queue */
	if (discard) {
		lck_mtx_lock_spin(buf_mtxp);
		CLR(bp->b_flags, (B_META | B_ZALLOC | B_DELWRI | B_LOCKED | B_AGE | B_ASYNC | B_NOCACHE | B_FUA));
		bp->b_whichq = BQ_EMPTY;
		binshash(bp, &invalhash);
		binsheadfree(bp, &bufqueues[BQ_EMPTY], BQ_EMPTY);
		CLR(bp->b_lflags, BL_BUSY);
		buf_busycount--;
	} else {
		/* Not discarding: clean up and prepare for reuse */
		bp->b_bufsize = 0;
		bp->b_datap = (uintptr_t)NULL;
		bp->b_upl = (void *)NULL;
		bp->b_fsprivate = (void *)NULL;
		/*
		 * preserve the state of whether this buffer
		 * was allocated on the fly or not...
		 * the only other flag that should be set at
		 * this point is BL_BUSY...
		 */
#ifdef JOE_DEBUG
		bp->b_owner = current_thread();
		bp->b_tag   = 3;
#endif
		bp->b_lflags = BL_BUSY;
		bp->b_flags = (bp->b_flags & B_HDRALLOC);
		bp->b_redundancy_flags = 0;
		bp->b_dev = NODEV;
		bp->b_blkno = bp->b_lblkno = 0;
		bp->b_iodone = NULL;
		bp->b_error = 0;
		bp->b_resid = 0;
		bp->b_bcount = 0;
		bp->b_dirtyoff = bp->b_dirtyend = 0;
		bp->b_validoff = bp->b_validend = 0;
		bzero(&bp->b_attr, sizeof(struct bufattr));

		lck_mtx_lock_spin(buf_mtxp);
	}
	return (0);
}