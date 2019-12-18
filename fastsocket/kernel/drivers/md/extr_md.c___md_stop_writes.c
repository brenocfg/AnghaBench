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
struct mddev {scalar_t__ ro; int in_sync; scalar_t__ flags; int /*<<< orphan*/  safemode_timer; int /*<<< orphan*/  recovery; scalar_t__ sync_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  bitmap_flush (struct mddev*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_reap_sync_thread (struct mddev*) ; 
 int /*<<< orphan*/  md_super_wait (struct mddev*) ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __md_stop_writes(struct mddev *mddev)
{
	set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	if (mddev->sync_thread) {
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		md_reap_sync_thread(mddev);
	}

	del_timer_sync(&mddev->safemode_timer);

	bitmap_flush(mddev);
	md_super_wait(mddev);

	if (mddev->ro == 0 &&
	    (!mddev->in_sync || mddev->flags)) {
		/* mark array as shutdown cleanly */
		mddev->in_sync = 1;
		md_update_sb(mddev, 1);
	}
}