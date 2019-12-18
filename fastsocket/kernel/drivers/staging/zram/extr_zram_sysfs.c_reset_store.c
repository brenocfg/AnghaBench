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
struct zram {int /*<<< orphan*/  init_lock; scalar_t__ init_done; int /*<<< orphan*/  disk; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct block_device {scalar_t__ bd_holders; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  __zram_reset_device (struct zram*) ; 
 struct block_device* bdget_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsync_bdev (struct block_device*) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t reset_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	int ret;
	unsigned long do_reset;
	struct zram *zram;
	struct block_device *bdev;

	zram = dev_to_zram(dev);
	bdev = bdget_disk(zram->disk, 0);

	/* Do not reset an active device! */
	if (bdev->bd_holders)
		return -EBUSY;

	ret = strict_strtoul(buf, 10, &do_reset);
	if (ret)
		return ret;

	if (!do_reset)
		return -EINVAL;

	/* Make sure all pending I/O is finished */
	if (bdev)
		fsync_bdev(bdev);

	down_write(&zram->init_lock);
	if (zram->init_done)
		__zram_reset_device(zram);
	up_write(&zram->init_lock);

	return len;
}