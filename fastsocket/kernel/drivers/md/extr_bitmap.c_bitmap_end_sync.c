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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct bitmap {TYPE_1__ counts; scalar_t__ allclean; } ;
typedef  int sector_t ;
typedef  int bitmap_counter_t ;

/* Variables and functions */
 int /*<<< orphan*/  NEEDED (int) ; 
 int NEEDED_MASK ; 
 scalar_t__ RESYNC (int) ; 
 int RESYNC_MASK ; 
 int* bitmap_get_counter (TYPE_1__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_pending (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void bitmap_end_sync(struct bitmap *bitmap, sector_t offset, sector_t *blocks, int aborted)
{
	bitmap_counter_t *bmc;
	unsigned long flags;

	if (bitmap == NULL) {
		*blocks = 1024;
		return;
	}
	spin_lock_irqsave(&bitmap->counts.lock, flags);
	bmc = bitmap_get_counter(&bitmap->counts, offset, blocks, 0);
	if (bmc == NULL)
		goto unlock;
	/* locked */
	if (RESYNC(*bmc)) {
		*bmc &= ~RESYNC_MASK;

		if (!NEEDED(*bmc) && aborted)
			*bmc |= NEEDED_MASK;
		else {
			if (*bmc <= 2) {
				bitmap_set_pending(&bitmap->counts, offset);
				bitmap->allclean = 0;
			}
		}
	}
 unlock:
	spin_unlock_irqrestore(&bitmap->counts.lock, flags);
}