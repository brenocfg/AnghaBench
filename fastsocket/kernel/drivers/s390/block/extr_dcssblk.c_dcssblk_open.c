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
struct dcssblk_dev_info {int /*<<< orphan*/  use_count; } ;
struct block_device {int bd_block_size; TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct dcssblk_dev_info* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dcssblk_open(struct block_device *bdev, fmode_t mode)
{
	struct dcssblk_dev_info *dev_info;
	int rc;

	dev_info = bdev->bd_disk->private_data;
	if (NULL == dev_info) {
		rc = -ENODEV;
		goto out;
	}
	atomic_inc(&dev_info->use_count);
	bdev->bd_block_size = 4096;
	rc = 0;
out:
	return rc;
}