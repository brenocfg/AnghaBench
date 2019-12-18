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
struct md_rdev {int raid_disk; int saved_raid_disk; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; TYPE_2__* mddev; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int raid_disks; int delta_disks; TYPE_1__* pers; int /*<<< orphan*/  recovery; int /*<<< orphan*/  thread; } ;
struct TYPE_5__ {int (* hot_add_disk ) (TYPE_2__*,struct md_rdev*) ;int /*<<< orphan*/ * hot_remove_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  Blocked ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 int /*<<< orphan*/  WriteMostly ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_and_add_spares (TYPE_2__*,struct md_rdev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int simple_strtoul (char const*,char**,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int stub1 (TYPE_2__*,struct md_rdev*) ; 
 scalar_t__ sysfs_link_rdev (TYPE_2__*,struct md_rdev*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
slot_store(struct md_rdev *rdev, const char *buf, size_t len)
{
	char *e;
	int err;
	int slot = simple_strtoul(buf, &e, 10);
	if (strncmp(buf, "none", 4)==0)
		slot = -1;
	else if (e==buf || (*e && *e!= '\n'))
		return -EINVAL;
	if (rdev->mddev->pers && slot == -1) {
		/* Setting 'slot' on an active array requires also
		 * updating the 'rd%d' link, and communicating
		 * with the personality with ->hot_*_disk.
		 * For now we only support removing
		 * failed/spare devices.  This normally happens automatically,
		 * but not when the metadata is externally managed.
		 */
		if (rdev->raid_disk == -1)
			return -EEXIST;
		/* personality does all needed checks */
		if (rdev->mddev->pers->hot_remove_disk == NULL)
			return -EINVAL;
		clear_bit(Blocked, &rdev->flags);
		remove_and_add_spares(rdev->mddev, rdev);
		if (rdev->raid_disk >= 0)
			return -EBUSY;
		set_bit(MD_RECOVERY_NEEDED, &rdev->mddev->recovery);
		md_wakeup_thread(rdev->mddev->thread);
	} else if (rdev->mddev->pers) {
		/* Activating a spare .. or possibly reactivating
		 * if we ever get bitmaps working here.
		 */

		if (rdev->raid_disk != -1)
			return -EBUSY;

		if (test_bit(MD_RECOVERY_RUNNING, &rdev->mddev->recovery))
			return -EBUSY;

		if (rdev->mddev->pers->hot_add_disk == NULL)
			return -EINVAL;

		if (slot >= rdev->mddev->raid_disks &&
		    slot >= rdev->mddev->raid_disks + rdev->mddev->delta_disks)
			return -ENOSPC;

		rdev->raid_disk = slot;
		if (test_bit(In_sync, &rdev->flags))
			rdev->saved_raid_disk = slot;
		else
			rdev->saved_raid_disk = -1;
		clear_bit(In_sync, &rdev->flags);
		err = rdev->mddev->pers->
			hot_add_disk(rdev->mddev, rdev);
		if (err) {
			rdev->raid_disk = -1;
			return err;
		} else
			sysfs_notify_dirent_safe(rdev->sysfs_state);
		if (sysfs_link_rdev(rdev->mddev, rdev))
			/* failure here is OK */;
		/* don't wakeup anyone, leave that to userspace. */
	} else {
		if (slot >= rdev->mddev->raid_disks &&
		    slot >= rdev->mddev->raid_disks + rdev->mddev->delta_disks)
			return -ENOSPC;
		rdev->raid_disk = slot;
		/* assume it is working */
		clear_bit(Faulty, &rdev->flags);
		clear_bit(WriteMostly, &rdev->flags);
		set_bit(In_sync, &rdev->flags);
		sysfs_notify_dirent_safe(rdev->sysfs_state);
	}
	return len;
}