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
struct loop_device {scalar_t__ lo_state; int lo_refcnt; int /*<<< orphan*/  lo_ctl_mutex; int /*<<< orphan*/  lo_disk; int /*<<< orphan*/  lo_file_name; int /*<<< orphan*/  lo_crypt_name; int /*<<< orphan*/  lo_encrypt_key; int /*<<< orphan*/ * lo_thread; scalar_t__ lo_flags; scalar_t__ lo_encrypt_key_size; scalar_t__ lo_sizelimit; scalar_t__ lo_offset; int /*<<< orphan*/ * lo_encryption; int /*<<< orphan*/ * lo_device; int /*<<< orphan*/ * ioctl; int /*<<< orphan*/ * transfer; struct file* lo_backing_file; TYPE_1__* lo_queue; int /*<<< orphan*/  lo_lock; int /*<<< orphan*/  old_gfp_mask; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/ * unplug_fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKRRPART ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  LO_KEY_SIZE ; 
 int /*<<< orphan*/  LO_NAME_SIZE ; 
 scalar_t__ Lo_bound ; 
 scalar_t__ Lo_rundown ; 
 scalar_t__ Lo_unbound ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bd_set_size (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  invalidate_bdev (struct block_device*) ; 
 int /*<<< orphan*/  ioctl_by_bdev (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loop_release_xfer (struct loop_device*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max_part ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loop_clr_fd(struct loop_device *lo, struct block_device *bdev)
{
	struct file *filp = lo->lo_backing_file;
	gfp_t gfp = lo->old_gfp_mask;

	if (lo->lo_state != Lo_bound)
		return -ENXIO;

	if (lo->lo_refcnt > 1)	/* we needed one fd for the ioctl */
		return -EBUSY;

	if (filp == NULL)
		return -EINVAL;

	spin_lock_irq(&lo->lo_lock);
	lo->lo_state = Lo_rundown;
	spin_unlock_irq(&lo->lo_lock);

	kthread_stop(lo->lo_thread);

	lo->lo_queue->unplug_fn = NULL;
	lo->lo_backing_file = NULL;

	loop_release_xfer(lo);
	lo->transfer = NULL;
	lo->ioctl = NULL;
	lo->lo_device = NULL;
	lo->lo_encryption = NULL;
	lo->lo_offset = 0;
	lo->lo_sizelimit = 0;
	lo->lo_encrypt_key_size = 0;
	lo->lo_flags = 0;
	lo->lo_thread = NULL;
	memset(lo->lo_encrypt_key, 0, LO_KEY_SIZE);
	memset(lo->lo_crypt_name, 0, LO_NAME_SIZE);
	memset(lo->lo_file_name, 0, LO_NAME_SIZE);
	if (bdev)
		invalidate_bdev(bdev);
	set_capacity(lo->lo_disk, 0);
	if (bdev)
		bd_set_size(bdev, 0);
	mapping_set_gfp_mask(filp->f_mapping, gfp);
	lo->lo_state = Lo_unbound;
	/* This is safe: open() is still holding a reference. */
	module_put(THIS_MODULE);
	if (max_part > 0 && bdev)
		ioctl_by_bdev(bdev, BLKRRPART, 0);
	mutex_unlock(&lo->lo_ctl_mutex);
	/*
	 * Need not hold lo_ctl_mutex to fput backing file.
	 * Calling fput holding lo_ctl_mutex triggers a circular
	 * lock dependency possibility warning as fput can take
	 * bd_mutex which is usually taken before lo_ctl_mutex.
	 */
	fput(filp);
	return 0;
}