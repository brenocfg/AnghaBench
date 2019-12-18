#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  TYPE_4__* proc_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  TYPE_5__* buf_t ;
struct TYPE_19__ {scalar_t__ b_datap; int /*<<< orphan*/  b_lblkno; int /*<<< orphan*/  b_bcount; int /*<<< orphan*/  b_flags; TYPE_3__* b_vp; } ;
struct TYPE_18__ {TYPE_2__* p_stats; } ;
struct TYPE_17__ {int /*<<< orphan*/  v_numoutput; } ;
struct TYPE_15__ {int /*<<< orphan*/  ru_oublock; } ;
struct TYPE_16__ {TYPE_1__ p_ru; } ;

/* Variables and functions */
 int B_ASYNC ; 
 int B_DELWRI ; 
 int B_DONE ; 
 int B_ERROR ; 
 int B_READ ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int ISSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomicLong (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TR_BUFWRITE ; 
 int /*<<< orphan*/  VNOP_STRATEGY (TYPE_5__*) ; 
 scalar_t__ brecover_data (TYPE_5__*) ; 
 int /*<<< orphan*/  buf_biowait (TYPE_5__*) ; 
 int /*<<< orphan*/  buf_brelse (TYPE_5__*) ; 
 int /*<<< orphan*/  buf_reassign (TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* current_proc () ; 
 int /*<<< orphan*/  nbdwrite ; 
 int /*<<< orphan*/  pack (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
buf_bwrite(buf_t bp)
{
	int	sync, wasdelayed;
	errno_t	rv;
	proc_t	p = current_proc();
	vnode_t	vp = bp->b_vp;

	if (bp->b_datap == 0) {
	        if (brecover_data(bp) == 0)
		        return (0);
	}
	/* Remember buffer type, to switch on it later. */
	sync = !ISSET(bp->b_flags, B_ASYNC);
	wasdelayed = ISSET(bp->b_flags, B_DELWRI);
	CLR(bp->b_flags, (B_READ | B_DONE | B_ERROR | B_DELWRI));

	if (wasdelayed)
		OSAddAtomicLong(-1, &nbdwrite);

	if (!sync) {
		/*
		 * If not synchronous, pay for the I/O operation and make
		 * sure the buf is on the correct vnode queue.  We have
		 * to do this now, because if we don't, the vnode may not
		 * be properly notified that its I/O has completed.
		 */
		if (wasdelayed)
			buf_reassign(bp, vp);
		else 
			if (p && p->p_stats) {
				OSIncrementAtomicLong(&p->p_stats->p_ru.ru_oublock);	/* XXX */
			}
	}
	trace(TR_BUFWRITE, pack(vp, bp->b_bcount), bp->b_lblkno);

	/* Initiate disk write.  Make sure the appropriate party is charged. */

        OSAddAtomic(1, &vp->v_numoutput);
	
	VNOP_STRATEGY(bp);

	if (sync) {
		/*
		 * If I/O was synchronous, wait for it to complete.
		 */
		rv = buf_biowait(bp);

		/*
		 * Pay for the I/O operation, if it's not been paid for, and
		 * make sure it's on the correct vnode queue. (async operatings
		 * were payed for above.)
		 */
		if (wasdelayed)
			buf_reassign(bp, vp);
		else
			if (p && p->p_stats) { 
				OSIncrementAtomicLong(&p->p_stats->p_ru.ru_oublock);	/* XXX */
			}

		/* Release the buffer. */
		buf_brelse(bp);

		return (rv);
	} else {
		return (0);
	}
}