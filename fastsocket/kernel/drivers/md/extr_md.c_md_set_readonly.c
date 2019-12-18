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
struct mddev {int ro; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  recovery; int /*<<< orphan*/  gendisk; scalar_t__ pers; int /*<<< orphan*/  openers; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  __md_stop_writes (struct mddev*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sync_blockdev (struct block_device*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int md_set_readonly(struct mddev *mddev, struct block_device *bdev)
{
	int err = 0;
	mutex_lock(&mddev->open_mutex);
	if (atomic_read(&mddev->openers) > !!bdev) {
		printk("md: %s still in use.\n",mdname(mddev));
		err = -EBUSY;
		goto out;
	}
	if (bdev)
		sync_blockdev(bdev);
	if (mddev->pers) {
		__md_stop_writes(mddev);

		err  = -ENXIO;
		if (mddev->ro==1)
			goto out;
		mddev->ro = 1;
		set_disk_ro(mddev->gendisk, 1);
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		sysfs_notify_dirent_safe(mddev->sysfs_state);
		err = 0;	
	}
out:
	mutex_unlock(&mddev->open_mutex);
	return err;
}