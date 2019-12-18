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
struct request_queue {int dummy; } ;
struct dm_target {int dummy; } ;
struct dm_dev {struct block_device* bdev; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int dm_queue_merge_is_compulsory (struct request_queue*) ; 

__attribute__((used)) static int dm_device_merge_is_compulsory(struct dm_target *ti,
					 struct dm_dev *dev, sector_t start,
					 sector_t len, void *data)
{
	struct block_device *bdev = dev->bdev;
	struct request_queue *q = bdev_get_queue(bdev);

	return dm_queue_merge_is_compulsory(q);
}