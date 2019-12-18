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
struct loop_device {int lo_flags; int /*<<< orphan*/  lo_ctl_mutex; scalar_t__ lo_refcnt; } ;
struct gendisk {struct loop_device* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int LO_FLAGS_AUTOCLEAR ; 
 int loop_clr_fd (struct loop_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_flush (struct loop_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lo_release(struct gendisk *disk, fmode_t mode)
{
	struct loop_device *lo = disk->private_data;
	int err;

	mutex_lock(&lo->lo_ctl_mutex);

	if (--lo->lo_refcnt)
		goto out;

	if (lo->lo_flags & LO_FLAGS_AUTOCLEAR) {
		/*
		 * In autoclear mode, stop the loop thread
		 * and remove configuration after last close.
		 */
		err = loop_clr_fd(lo, NULL);
		if (!err)
			goto out_unlocked;
	} else {
		/*
		 * Otherwise keep thread (if running) and config,
		 * but flush possible ongoing bios in thread.
		 */
		loop_flush(lo);
	}

out:
	mutex_unlock(&lo->lo_ctl_mutex);
out_unlocked:
	return 0;
}