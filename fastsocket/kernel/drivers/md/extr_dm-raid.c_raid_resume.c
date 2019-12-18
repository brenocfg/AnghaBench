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
struct TYPE_3__ {int /*<<< orphan*/  recovery; int /*<<< orphan*/  flags; } ;
struct raid_set {int bitmap_loaded; TYPE_1__ md; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CHANGE_DEVS ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  attempt_restore_of_faulty_devices (struct raid_set*) ; 
 int /*<<< orphan*/  bitmap_load (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mddev_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid_resume(struct dm_target *ti)
{
	struct raid_set *rs = ti->private;

	set_bit(MD_CHANGE_DEVS, &rs->md.flags);
	if (!rs->bitmap_loaded) {
		bitmap_load(&rs->md);
		rs->bitmap_loaded = 1;
	} else {
		/*
		 * A secondary resume while the device is active.
		 * Take this opportunity to check whether any failed
		 * devices are reachable again.
		 */
		attempt_restore_of_faulty_devices(rs);
	}

	clear_bit(MD_RECOVERY_FROZEN, &rs->md.recovery);
	mddev_resume(&rs->md);
}