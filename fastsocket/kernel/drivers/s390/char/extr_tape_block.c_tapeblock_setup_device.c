#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tape_blk_data {int medium_changed; TYPE_1__* request_queue; int /*<<< orphan*/  requeue_task; struct gendisk* disk; int /*<<< orphan*/  request_queue_lock; int /*<<< orphan*/  requeue_scheduled; struct tape_device* device; } ;
struct tape_device {int first_minor; struct tape_blk_data blk_data; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; TYPE_1__* queue; void* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
struct TYPE_9__ {void* queuedata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAPEBLOCK_HSEC_SIZE ; 
 int /*<<< orphan*/  TAPEBLOCK_MAX_SEC ; 
 int TAPE_MINORS_PER_DEV ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 struct gendisk* alloc_disk (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_1__*) ; 
 TYPE_1__* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (TYPE_1__*,long) ; 
 int /*<<< orphan*/  blk_queue_max_segments (TYPE_1__*,long) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (TYPE_1__*,long) ; 
 int elevator_change (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 void* tape_get_device_reference (struct tape_device*) ; 
 int /*<<< orphan*/  tapeblock_fops ; 
 int /*<<< orphan*/  tapeblock_major ; 
 int /*<<< orphan*/  tapeblock_request_fn ; 
 int /*<<< orphan*/  tapeblock_requeue ; 

int
tapeblock_setup_device(struct tape_device * device)
{
	struct tape_blk_data *	blkdat;
	struct gendisk *	disk;
	int			rc;

	blkdat = &device->blk_data;
	blkdat->device = device;
	spin_lock_init(&blkdat->request_queue_lock);
	atomic_set(&blkdat->requeue_scheduled, 0);

	blkdat->request_queue = blk_init_queue(
		tapeblock_request_fn,
		&blkdat->request_queue_lock
	);
	if (!blkdat->request_queue)
		return -ENOMEM;

	rc = elevator_change(blkdat->request_queue, "noop");
	if (rc)
		goto cleanup_queue;

	blk_queue_logical_block_size(blkdat->request_queue, TAPEBLOCK_HSEC_SIZE);
	blk_queue_max_hw_sectors(blkdat->request_queue, TAPEBLOCK_MAX_SEC);
	blk_queue_max_segments(blkdat->request_queue, -1L);
	blk_queue_max_segment_size(blkdat->request_queue, -1L);
	blk_queue_segment_boundary(blkdat->request_queue, -1L);

	disk = alloc_disk(1);
	if (!disk) {
		rc = -ENOMEM;
		goto cleanup_queue;
	}

	disk->major = tapeblock_major;
	disk->first_minor = device->first_minor;
	disk->fops = &tapeblock_fops;
	disk->private_data = tape_get_device_reference(device);
	disk->queue = blkdat->request_queue;
	set_capacity(disk, 0);
	sprintf(disk->disk_name, "btibm%d",
		device->first_minor / TAPE_MINORS_PER_DEV);

	blkdat->disk = disk;
	blkdat->medium_changed = 1;
	blkdat->request_queue->queuedata = tape_get_device_reference(device);

	add_disk(disk);

	tape_get_device_reference(device);
	INIT_WORK(&blkdat->requeue_task, tapeblock_requeue);

	return 0;

cleanup_queue:
	blk_cleanup_queue(blkdat->request_queue);
	blkdat->request_queue = NULL;

	return rc;
}