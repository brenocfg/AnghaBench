#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct bitmap {TYPE_1__ counts; scalar_t__ allclean; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int bitmap_counter_t ;

/* Variables and functions */
 int NEEDED_MASK ; 
 int /*<<< orphan*/  bitmap_count_page (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int* bitmap_get_counter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitmap_set_pending (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bitmap_set_memory_bits(struct bitmap *bitmap, sector_t offset, int needed)
{
	/* For each chunk covered by any of these sectors, set the
	 * counter to 2 and possibly set resync_needed.  They should all
	 * be 0 at this point
	 */

	sector_t secs;
	bitmap_counter_t *bmc;
	spin_lock_irq(&bitmap->counts.lock);
	bmc = bitmap_get_counter(&bitmap->counts, offset, &secs, 1);
	if (!bmc) {
		spin_unlock_irq(&bitmap->counts.lock);
		return;
	}
	if (!*bmc) {
		*bmc = 2 | (needed ? NEEDED_MASK : 0);
		bitmap_count_page(&bitmap->counts, offset, 1);
		bitmap_set_pending(&bitmap->counts, offset);
		bitmap->allclean = 0;
	}
	spin_unlock_irq(&bitmap->counts.lock);
}