#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bqueues {int /*<<< orphan*/ ** tqh_last; } ;
typedef  TYPE_2__* buf_t ;
struct TYPE_5__ {int /*<<< orphan*/ * tqe_next; } ;
struct TYPE_6__ {int b_whichq; scalar_t__ b_shadow_ref; scalar_t__ b_shadow; scalar_t__ b_timestamp; TYPE_1__ b_freelist; } ;

/* Variables and functions */
 int BQ_LAUNDRY ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct bqueues*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_freelist ; 
 int /*<<< orphan*/  blaundrycnt ; 
 struct bqueues* bufqueues ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static void
bremfree_locked(buf_t bp)
{
	struct bqueues *dp = NULL;
	int whichq;

	whichq = bp->b_whichq;

	if (whichq == -1) {
		if (bp->b_shadow_ref == 0)
			panic("bremfree_locked: %p not on freelist", bp);
		/*
		 * there are clones pointing to 'bp'...
		 * therefore, it was not put on a freelist
		 * when buf_brelse was last called on 'bp'
		 */
		return;
	}
	/*
	 * We only calculate the head of the freelist when removing
	 * the last element of the list as that is the only time that
	 * it is needed (e.g. to reset the tail pointer).
	 *
	 * NB: This makes an assumption about how tailq's are implemented.
	 */
	if (bp->b_freelist.tqe_next == NULL) {
	        dp = &bufqueues[whichq];

		if (dp->tqh_last != &bp->b_freelist.tqe_next)
			panic("bremfree: lost tail");
	}
	TAILQ_REMOVE(dp, bp, b_freelist);

	if (whichq == BQ_LAUNDRY)
	        blaundrycnt--;

	bp->b_whichq = -1;
	bp->b_timestamp = 0; 
	bp->b_shadow = 0;
}