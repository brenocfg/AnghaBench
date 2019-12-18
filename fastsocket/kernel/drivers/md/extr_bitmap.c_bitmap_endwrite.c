#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct bitmap {scalar_t__ events_cleared; int need_sync; TYPE_3__ counts; scalar_t__ allclean; int /*<<< orphan*/  overflow_wait; int /*<<< orphan*/  sysfs_can_clear; TYPE_2__* mddev; int /*<<< orphan*/  behind_writes; int /*<<< orphan*/  behind_wait; } ;
typedef  unsigned long sector_t ;
typedef  int bitmap_counter_t ;
struct TYPE_5__ {int /*<<< orphan*/  max_write_behind; } ;
struct TYPE_6__ {scalar_t__ events; int /*<<< orphan*/  degraded; TYPE_1__ bitmap_info; } ;

/* Variables and functions */
 scalar_t__ COUNTER (int) ; 
 scalar_t__ COUNTER_MAX ; 
 int /*<<< orphan*/  NEEDED (int) ; 
 int NEEDED_MASK ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int* bitmap_get_counter (TYPE_3__*,unsigned long,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_pending (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void bitmap_endwrite(struct bitmap *bitmap, sector_t offset, unsigned long sectors,
		     int success, int behind)
{
	if (!bitmap)
		return;
	if (behind) {
		if (atomic_dec_and_test(&bitmap->behind_writes))
			wake_up(&bitmap->behind_wait);
		pr_debug("dec write-behind count %d/%lu\n",
			 atomic_read(&bitmap->behind_writes),
			 bitmap->mddev->bitmap_info.max_write_behind);
	}

	while (sectors) {
		sector_t blocks;
		unsigned long flags;
		bitmap_counter_t *bmc;

		spin_lock_irqsave(&bitmap->counts.lock, flags);
		bmc = bitmap_get_counter(&bitmap->counts, offset, &blocks, 0);
		if (!bmc) {
			spin_unlock_irqrestore(&bitmap->counts.lock, flags);
			return;
		}

		if (success && !bitmap->mddev->degraded &&
		    bitmap->events_cleared < bitmap->mddev->events) {
			bitmap->events_cleared = bitmap->mddev->events;
			bitmap->need_sync = 1;
			sysfs_notify_dirent_safe(bitmap->sysfs_can_clear);
		}

		if (!success && !NEEDED(*bmc))
			*bmc |= NEEDED_MASK;

		if (COUNTER(*bmc) == COUNTER_MAX)
			wake_up(&bitmap->overflow_wait);

		(*bmc)--;
		if (*bmc <= 2) {
			bitmap_set_pending(&bitmap->counts, offset);
			bitmap->allclean = 0;
		}
		spin_unlock_irqrestore(&bitmap->counts.lock, flags);
		offset += blocks;
		if (sectors > blocks)
			sectors -= blocks;
		else
			sectors = 0;
	}
}