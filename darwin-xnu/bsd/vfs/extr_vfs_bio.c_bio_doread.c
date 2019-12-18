#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
struct proc {TYPE_2__* p_stats; } ;
struct buf {int /*<<< orphan*/  b_rcred; int /*<<< orphan*/  b_flags; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  daddr64_t ;
typedef  struct buf* buf_t ;
struct TYPE_3__ {int /*<<< orphan*/  ru_inblock; } ;
struct TYPE_4__ {TYPE_1__ p_ru; } ;

/* Variables and functions */
 int B_DELWRI ; 
 int B_DONE ; 
 int B_READ ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TR_BREADHIT ; 
 int /*<<< orphan*/  TR_BREADMISS ; 
 int /*<<< orphan*/  VNOP_STRATEGY (struct buf*) ; 
 int /*<<< orphan*/  buf_brelse (struct buf*) ; 
 struct buf* buf_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buf *
bio_doread(vnode_t vp, daddr64_t blkno, int size, kauth_cred_t cred, int async, int queuetype)
{
	buf_t	bp;

	bp = buf_getblk(vp, blkno, size, 0, 0, queuetype);

	/*
	 * If buffer does not have data valid, start a read.
	 * Note that if buffer is B_INVAL, buf_getblk() won't return it.
	 * Therefore, it's valid if it's I/O has completed or been delayed.
	 */
	if (!ISSET(bp->b_flags, (B_DONE | B_DELWRI))) {
		struct proc *p;

		p = current_proc();

		/* Start I/O for the buffer (keeping credentials). */
		SET(bp->b_flags, B_READ | async);
		if (IS_VALID_CRED(cred) && !IS_VALID_CRED(bp->b_rcred)) {
			kauth_cred_ref(cred);
			bp->b_rcred = cred;
		}

		VNOP_STRATEGY(bp);

		trace(TR_BREADMISS, pack(vp, size), blkno);

		/* Pay for the read. */
		if (p && p->p_stats) { 
			OSIncrementAtomicLong(&p->p_stats->p_ru.ru_inblock);		/* XXX */
		}

		if (async) {
		        /*
			 * since we asked for an ASYNC I/O
			 * the biodone will do the brelse
			 * we don't want to pass back a bp
			 * that we don't 'own'
			 */
		        bp = NULL;
		}
	} else if (async) {
		buf_brelse(bp);
		bp = NULL;
	}

	trace(TR_BREADHIT, pack(vp, size), blkno);

	return (bp);
}