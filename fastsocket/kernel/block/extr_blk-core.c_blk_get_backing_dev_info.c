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
struct backing_dev_info {int dummy; } ;
struct request_queue {struct backing_dev_info backing_dev_info; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (struct block_device*) ; 

struct backing_dev_info *blk_get_backing_dev_info(struct block_device *bdev)
{
	struct backing_dev_info *ret = NULL;
	struct request_queue *q = bdev_get_queue(bdev);

	if (q)
		ret = &q->backing_dev_info;
	return ret;
}