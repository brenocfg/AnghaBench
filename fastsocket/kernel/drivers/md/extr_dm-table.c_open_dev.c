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
struct mapped_device {int dummy; } ;
struct TYPE_2__ {struct block_device* bdev; int /*<<< orphan*/  mode; } ;
struct dm_dev_internal {TYPE_1__ dm_dev; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct block_device*) ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int PTR_ERR (struct block_device*) ; 
 int bd_claim_by_disk (struct block_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_disk (struct mapped_device*) ; 
 struct block_device* open_by_devnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_dev(struct dm_dev_internal *d, dev_t dev,
		    struct mapped_device *md)
{
	static char *_claim_ptr = "I belong to device-mapper";
	struct block_device *bdev;

	int r;

	BUG_ON(d->dm_dev.bdev);

	bdev = open_by_devnum(dev, d->dm_dev.mode);
	if (IS_ERR(bdev))
		return PTR_ERR(bdev);
	r = bd_claim_by_disk(bdev, _claim_ptr, dm_disk(md));
	if (r)
		blkdev_put(bdev, d->dm_dev.mode);
	else
		d->dm_dev.bdev = bdev;
	return r;
}