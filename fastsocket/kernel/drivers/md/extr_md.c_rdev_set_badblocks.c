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
struct md_rdev {TYPE_1__* mddev; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  badblocks; scalar_t__ data_offset; scalar_t__ new_data_offset; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CHANGE_CLEAN ; 
 int md_set_badblocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 

int rdev_set_badblocks(struct md_rdev *rdev, sector_t s, int sectors,
		       int is_new)
{
	int rv;
	if (is_new)
		s += rdev->new_data_offset;
	else
		s += rdev->data_offset;
	rv = md_set_badblocks(&rdev->badblocks,
			      s, sectors, 0);
	if (rv) {
		/* Make sure they get written out promptly */
		sysfs_notify_dirent_safe(rdev->sysfs_state);
		set_bit(MD_CHANGE_CLEAN, &rdev->mddev->flags);
		md_wakeup_thread(rdev->mddev->thread);
	}
	return rv;
}