#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct zram {scalar_t__ init_done; TYPE_1__* disk; TYPE_4__* queue; int /*<<< orphan*/  stat64_lock; int /*<<< orphan*/  init_lock; int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {struct zram* queuedata; } ;
struct TYPE_14__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_13__ {int first_minor; TYPE_4__* queue; int /*<<< orphan*/  disk_name; struct zram* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ZRAM_LOGICAL_BLOCK_SIZE ; 
 int /*<<< orphan*/  add_disk (TYPE_1__*) ; 
 TYPE_1__* alloc_disk (int) ; 
 TYPE_4__* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  blk_queue_io_min (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_io_opt (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_make_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* disk_to_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  set_capacity (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zram_devops ; 
 int /*<<< orphan*/  zram_disk_attr_group ; 
 int /*<<< orphan*/  zram_major ; 
 int /*<<< orphan*/  zram_make_request ; 

__attribute__((used)) static int create_device(struct zram *zram, int device_id)
{
	int ret = 0;

	init_rwsem(&zram->lock);
	init_rwsem(&zram->init_lock);
	spin_lock_init(&zram->stat64_lock);

	zram->queue = blk_alloc_queue(GFP_KERNEL);
	if (!zram->queue) {
		pr_err("Error allocating disk queue for device %d\n",
			device_id);
		ret = -ENOMEM;
		goto out;
	}

	blk_queue_make_request(zram->queue, zram_make_request);
	zram->queue->queuedata = zram;

	 /* gendisk structure */
	zram->disk = alloc_disk(1);
	if (!zram->disk) {
		blk_cleanup_queue(zram->queue);
		pr_warning("Error allocating disk structure for device %d\n",
			device_id);
		ret = -ENOMEM;
		goto out;
	}

	zram->disk->major = zram_major;
	zram->disk->first_minor = device_id;
	zram->disk->fops = &zram_devops;
	zram->disk->queue = zram->queue;
	zram->disk->private_data = zram;
	snprintf(zram->disk->disk_name, 16, "zram%d", device_id);

	/* Actual capacity set using syfs (/sys/block/zram<id>/disksize */
	set_capacity(zram->disk, 0);

	/*
	 * To ensure that we always get PAGE_SIZE aligned
	 * and n*PAGE_SIZED sized I/O requests.
	 */
	blk_queue_physical_block_size(zram->disk->queue, PAGE_SIZE);
	blk_queue_logical_block_size(zram->disk->queue,
					ZRAM_LOGICAL_BLOCK_SIZE);
	blk_queue_io_min(zram->disk->queue, PAGE_SIZE);
	blk_queue_io_opt(zram->disk->queue, PAGE_SIZE);

	add_disk(zram->disk);

	ret = sysfs_create_group(&disk_to_dev(zram->disk)->kobj,
				&zram_disk_attr_group);
	if (ret < 0) {
		pr_warning("Error creating sysfs group");
		goto out;
	}

	zram->init_done = 0;

out:
	return ret;
}