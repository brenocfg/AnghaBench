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
typedef  int /*<<< orphan*/  u64 ;
struct zram {int disksize; int /*<<< orphan*/  init_lock; int /*<<< orphan*/  disk; scalar_t__ init_done; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 struct zram* dev_to_zram (struct device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int) ; 
 int strict_strtoull (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t disksize_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	int ret;
	u64 disksize;
	struct zram *zram = dev_to_zram(dev);

	ret = strict_strtoull(buf, 10, &disksize);
	if (ret)
		return ret;

	down_write(&zram->init_lock);
	if (zram->init_done) {
		up_write(&zram->init_lock);
		pr_info("Cannot change disksize for initialized device\n");
		return -EBUSY;
	}

	zram->disksize = PAGE_ALIGN(disksize);
	set_capacity(zram->disk, zram->disksize >> SECTOR_SHIFT);
	up_write(&zram->init_lock);

	return len;
}