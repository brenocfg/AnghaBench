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
struct se_device {int dummy; } ;
struct request_queue {int flush_flags; } ;
struct iblock_dev {struct block_device* ibd_bd; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 int REQ_FLUSH ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 

bool iblock_get_write_cache(struct se_device *dev)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);
	struct block_device *bd = ib_dev->ibd_bd;
	struct request_queue *q = bdev_get_queue(bd);

	return q->flush_flags & REQ_FLUSH;
}