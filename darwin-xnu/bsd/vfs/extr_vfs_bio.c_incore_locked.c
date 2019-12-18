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
typedef  scalar_t__ vnode_t ;
struct bufhashhdr {struct buf* lh_first; } ;
struct TYPE_2__ {struct buf* le_next; } ;
struct buf {scalar_t__ b_lblkno; scalar_t__ b_vp; int /*<<< orphan*/  b_flags; TYPE_1__ b_hash; } ;
typedef  scalar_t__ daddr64_t ;
typedef  struct buf* buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_INVAL ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static buf_t
incore_locked(vnode_t vp, daddr64_t blkno, struct bufhashhdr *dp)
{
	struct buf *bp;

	/* Search hash chain */
	for (bp = dp->lh_first; bp != NULL; bp = bp->b_hash.le_next) {
		if (bp->b_lblkno == blkno && bp->b_vp == vp &&
		    !ISSET(bp->b_flags, B_INVAL)) {
			return (bp);
		}
	}
	return (NULL);
}