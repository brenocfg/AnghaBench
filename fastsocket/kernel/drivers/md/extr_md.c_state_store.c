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
struct mddev {scalar_t__ pers; int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; } ;
struct TYPE_2__ {scalar_t__ unacked_exist; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; struct mddev* mddev; int /*<<< orphan*/  blocked_wait; TYPE_1__ badblocks; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  Blocked ; 
 int /*<<< orphan*/  BlockedBadBlocks ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 int /*<<< orphan*/  WriteErrorSeen ; 
 int /*<<< orphan*/  WriteMostly ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmd_match (char const*,char*) ; 
 int /*<<< orphan*/  kick_rdev_from_array (struct md_rdev*) ; 
 int /*<<< orphan*/  md_error (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  md_new_event (struct mddev*) ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
state_store(struct md_rdev *rdev, const char *buf, size_t len)
{
	/* can write
	 *  faulty  - simulates an error
	 *  remove  - disconnects the device
	 *  writemostly - sets write_mostly
	 *  -writemostly - clears write_mostly
	 *  blocked - sets the Blocked flags
	 *  -blocked - clears the Blocked and possibly simulates an error
	 *  insync - sets Insync providing device isn't active
	 *  write_error - sets WriteErrorSeen
	 *  -write_error - clears WriteErrorSeen
	 */
	int err = -EINVAL;
	if (cmd_match(buf, "faulty") && rdev->mddev->pers) {
		md_error(rdev->mddev, rdev);
		if (test_bit(Faulty, &rdev->flags))
			err = 0;
		else
			err = -EBUSY;
	} else if (cmd_match(buf, "remove")) {
		if (rdev->raid_disk >= 0)
			err = -EBUSY;
		else {
			struct mddev *mddev = rdev->mddev;
			kick_rdev_from_array(rdev);
			if (mddev->pers)
				md_update_sb(mddev, 1);
			md_new_event(mddev);
			err = 0;
		}
	} else if (cmd_match(buf, "writemostly")) {
		set_bit(WriteMostly, &rdev->flags);
		err = 0;
	} else if (cmd_match(buf, "-writemostly")) {
		clear_bit(WriteMostly, &rdev->flags);
		err = 0;
	} else if (cmd_match(buf, "blocked")) {
		set_bit(Blocked, &rdev->flags);
		err = 0;
	} else if (cmd_match(buf, "-blocked")) {
		if (!test_bit(Faulty, &rdev->flags) &&
		    rdev->badblocks.unacked_exist) {
			/* metadata handler doesn't understand badblocks,
			 * so we need to fail the device
			 */
			md_error(rdev->mddev, rdev);
		}
		clear_bit(Blocked, &rdev->flags);
		clear_bit(BlockedBadBlocks, &rdev->flags);
		wake_up(&rdev->blocked_wait);
		set_bit(MD_RECOVERY_NEEDED, &rdev->mddev->recovery);
		md_wakeup_thread(rdev->mddev->thread);

		err = 0;
	} else if (cmd_match(buf, "insync") && rdev->raid_disk == -1) {
		set_bit(In_sync, &rdev->flags);
		err = 0;
	} else if (cmd_match(buf, "write_error")) {
		set_bit(WriteErrorSeen, &rdev->flags);
		err = 0;
	} else if (cmd_match(buf, "-write_error")) {
		clear_bit(WriteErrorSeen, &rdev->flags);
		err = 0;
	} else if (cmd_match(buf, "want_replacement")) {
		/* Any non-spare device that is not a replacement can
		 * become want_replacement at any time, but we then need to
		 * check if recovery is needed.
		 */
		if (rdev->raid_disk >= 0 &&
		    !test_bit(Replacement, &rdev->flags))
			set_bit(WantReplacement, &rdev->flags);
		set_bit(MD_RECOVERY_NEEDED, &rdev->mddev->recovery);
		md_wakeup_thread(rdev->mddev->thread);
		err = 0;
	} else if (cmd_match(buf, "-want_replacement")) {
		/* Clearing 'want_replacement' is always allowed.
		 * Once replacements starts it is too late though.
		 */
		err = 0;
		clear_bit(WantReplacement, &rdev->flags);
	} else if (cmd_match(buf, "replacement")) {
		/* Can only set a device as a replacement when array has not
		 * yet been started.  Once running, replacement is automatic
		 * from spares, or by assigning 'slot'.
		 */
		if (rdev->mddev->pers)
			err = -EBUSY;
		else {
			set_bit(Replacement, &rdev->flags);
			err = 0;
		}
	} else if (cmd_match(buf, "-replacement")) {
		/* Similarly, can only clear Replacement before start */
		if (rdev->mddev->pers)
			err = -EBUSY;
		else {
			clear_bit(Replacement, &rdev->flags);
			err = 0;
		}
	}
	if (!err)
		sysfs_notify_dirent_safe(rdev->sysfs_state);
	return err ? err : len;
}