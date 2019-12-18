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
typedef  int /*<<< orphan*/  u64 ;
struct badblocks {int shift; int count; int changed; int /*<<< orphan*/  lock; int /*<<< orphan*/ * page; } ;
typedef  int sector_t ;

/* Variables and functions */
 int BB_ACK (int /*<<< orphan*/ ) ; 
 int BB_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BB_MAKE (int,int,int) ; 
 int BB_OFFSET (int /*<<< orphan*/ ) ; 
 int MD_MAX_BADBLOCKS ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_seqlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int md_clear_badblocks(struct badblocks *bb, sector_t s, int sectors)
{
	u64 *p;
	int lo, hi;
	sector_t target = s + sectors;
	int rv = 0;

	if (bb->shift > 0) {
		/* When clearing we round the start up and the end down.
		 * This should not matter as the shift should align with
		 * the block size and no rounding should ever be needed.
		 * However it is better the think a block is bad when it
		 * isn't than to think a block is not bad when it is.
		 */
		s += (1<<bb->shift) - 1;
		s >>= bb->shift;
		target >>= bb->shift;
		sectors = target - s;
	}

	write_seqlock_irq(&bb->lock);

	p = bb->page;
	lo = 0;
	hi = bb->count;
	/* Find the last range that starts before 'target' */
	while (hi - lo > 1) {
		int mid = (lo + hi) / 2;
		sector_t a = BB_OFFSET(p[mid]);
		if (a < target)
			lo = mid;
		else
			hi = mid;
	}
	if (hi > lo) {
		/* p[lo] is the last range that could overlap the
		 * current range.  Earlier ranges could also overlap,
		 * but only this one can overlap the end of the range.
		 */
		if (BB_OFFSET(p[lo]) + BB_LEN(p[lo]) > target) {
			/* Partial overlap, leave the tail of this range */
			int ack = BB_ACK(p[lo]);
			sector_t a = BB_OFFSET(p[lo]);
			sector_t end = a + BB_LEN(p[lo]);

			if (a < s) {
				/* we need to split this range */
				if (bb->count >= MD_MAX_BADBLOCKS) {
					rv = 0;
					goto out;
				}
				memmove(p+lo+1, p+lo, (bb->count - lo) * 8);
				bb->count++;
				p[lo] = BB_MAKE(a, s-a, ack);
				lo++;
			}
			p[lo] = BB_MAKE(target, end - target, ack);
			/* there is no longer an overlap */
			hi = lo;
			lo--;
		}
		while (lo >= 0 &&
		       BB_OFFSET(p[lo]) + BB_LEN(p[lo]) > s) {
			/* This range does overlap */
			if (BB_OFFSET(p[lo]) < s) {
				/* Keep the early parts of this range. */
				int ack = BB_ACK(p[lo]);
				sector_t start = BB_OFFSET(p[lo]);
				p[lo] = BB_MAKE(start, s - start, ack);
				/* now low doesn't overlap, so.. */
				break;
			}
			lo--;
		}
		/* 'lo' is strictly before, 'hi' is strictly after,
		 * anything between needs to be discarded
		 */
		if (hi - lo > 1) {
			memmove(p+lo+1, p+hi, (bb->count - hi) * 8);
			bb->count -= (hi - lo - 1);
		}
	}

	bb->changed = 1;
out:
	write_sequnlock_irq(&bb->lock);
	return rv;
}