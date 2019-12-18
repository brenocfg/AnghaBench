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
struct ocfs2_super {int /*<<< orphan*/  vol_state; int /*<<< orphan*/  osb_mount_event; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ VOLUME_DISABLED ; 
 scalar_t__ VOLUME_MOUNTED ; 
 scalar_t__ VOLUME_MOUNTED_QUOTAS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __ocfs2_wait_on_mount(struct ocfs2_super *osb, int quota)
{
	/* This check is good because ocfs2 will wait on our recovery
	 * thread before changing it to something other than MOUNTED
	 * or DISABLED. */
	wait_event(osb->osb_mount_event,
		  (!quota && atomic_read(&osb->vol_state) == VOLUME_MOUNTED) ||
		   atomic_read(&osb->vol_state) == VOLUME_MOUNTED_QUOTAS ||
		   atomic_read(&osb->vol_state) == VOLUME_DISABLED);

	/* If there's an error on mount, then we may never get to the
	 * MOUNTED flag, but this is set right before
	 * dismount_volume() so we can trust it. */
	if (atomic_read(&osb->vol_state) == VOLUME_DISABLED) {
		mlog(0, "mount error, exiting!\n");
		return -EBUSY;
	}

	return 0;
}