#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct driver_data {int instance; unsigned int index; int trim_supp; TYPE_3__* disk; TYPE_8__* queue; int /*<<< orphan*/ * mtip_svc_handler; TYPE_2__* pdev; int /*<<< orphan*/  dd_flag; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_20__ {int discard_granularity; scalar_t__ discard_zeroes_data; } ;
struct TYPE_24__ {TYPE_1__ limits; int /*<<< orphan*/  queue_flags; struct driver_data* queuedata; } ;
struct TYPE_23__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_22__ {int first_minor; TYPE_8__* queue; struct driver_data* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; int /*<<< orphan*/ * driverfs_dev; int /*<<< orphan*/  disk_name; } ;
struct TYPE_21__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_NAME_LEN ; 
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTIP_DDF_INIT_DONE_BIT ; 
 int MTIP_FTL_REBUILD_MAGIC ; 
 int MTIP_MAX_MINORS ; 
 int /*<<< orphan*/  MTIP_MAX_SG ; 
 int MTIP_MAX_TRIM_ENTRIES ; 
 int MTIP_MAX_TRIM_ENTRY_LEN ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  add_disk (TYPE_3__*) ; 
 TYPE_3__* alloc_disk (int) ; 
 TYPE_8__* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_8__*) ; 
 int /*<<< orphan*/  blk_queue_flush (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_io_min (TYPE_8__*,int) ; 
 int /*<<< orphan*/  blk_queue_make_request (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (TYPE_8__*,int) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (TYPE_8__*,int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (TYPE_8__*,int) ; 
 int /*<<< orphan*/  blk_queue_max_segments (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (TYPE_8__*,int) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_5__* disk_to_dev (TYPE_3__*) ; 
 int ida_get_new (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,unsigned int) ; 
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct driver_data*,unsigned char*) ; 
 int /*<<< orphan*/  mtip_block_ops ; 
 int /*<<< orphan*/  mtip_hw_debugfs_exit (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_debugfs_init (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_exit (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_get_capacity (struct driver_data*,int /*<<< orphan*/ *) ; 
 int mtip_hw_init (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_hw_sysfs_init (struct driver_data*,struct kobject*) ; 
 int /*<<< orphan*/  mtip_make_request ; 
 int /*<<< orphan*/  mtip_service_thread ; 
 int /*<<< orphan*/  put_disk (TYPE_3__*) ; 
 int rssd_disk_name_format (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rssd_index_ida ; 
 int /*<<< orphan*/  rssd_index_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (unsigned char*,char*,unsigned int) ; 

__attribute__((used)) static int mtip_block_initialize(struct driver_data *dd)
{
	int rv = 0, wait_for_rebuild = 0;
	sector_t capacity;
	unsigned int index = 0;
	struct kobject *kobj;
	unsigned char thd_name[16];

	if (dd->disk)
		goto skip_create_disk; /* hw init done, before rebuild */

	/* Initialize the protocol layer. */
	wait_for_rebuild = mtip_hw_init(dd);
	if (wait_for_rebuild < 0) {
		dev_err(&dd->pdev->dev,
			"Protocol layer initialization failed\n");
		rv = -EINVAL;
		goto protocol_init_error;
	}

	dd->disk = alloc_disk(MTIP_MAX_MINORS);
	if (dd->disk  == NULL) {
		dev_err(&dd->pdev->dev,
			"Unable to allocate gendisk structure\n");
		rv = -EINVAL;
		goto alloc_disk_error;
	}

	/* Generate the disk name, implemented same as in sd.c */
	do {
		if (!ida_pre_get(&rssd_index_ida, GFP_KERNEL))
			goto ida_get_error;

		spin_lock(&rssd_index_lock);
		rv = ida_get_new(&rssd_index_ida, &index);
		spin_unlock(&rssd_index_lock);
	} while (rv == -EAGAIN);

	if (rv)
		goto ida_get_error;

	rv = rssd_disk_name_format("rssd",
				index,
				dd->disk->disk_name,
				DISK_NAME_LEN);
	if (rv)
		goto disk_index_error;

	dd->disk->driverfs_dev	= &dd->pdev->dev;
	dd->disk->major		= dd->major;
	dd->disk->first_minor	= dd->instance * MTIP_MAX_MINORS;
	dd->disk->fops		= &mtip_block_ops;
	dd->disk->private_data	= dd;
	dd->index		= index;

	/*
	 * if rebuild pending, start the service thread, and delay the block
	 * queue creation and add_disk()
	 */
	if (wait_for_rebuild == MTIP_FTL_REBUILD_MAGIC)
		goto start_service_thread;

skip_create_disk:
	/* Allocate the request queue. */
	dd->queue = blk_alloc_queue(GFP_KERNEL);
	if (dd->queue == NULL) {
		dev_err(&dd->pdev->dev,
			"Unable to allocate request queue\n");
		rv = -ENOMEM;
		goto block_queue_alloc_init_error;
	}

	/* Attach our request function to the request queue. */
	blk_queue_make_request(dd->queue, mtip_make_request);

	dd->disk->queue		= dd->queue;
	dd->queue->queuedata	= dd;

	/* Set device limits. */
	set_bit(QUEUE_FLAG_NONROT, &dd->queue->queue_flags);
	blk_queue_max_segments(dd->queue, MTIP_MAX_SG);
	blk_queue_physical_block_size(dd->queue, 4096);
	blk_queue_max_hw_sectors(dd->queue, 0xffff);
	blk_queue_max_segment_size(dd->queue, 0x400000);
	blk_queue_io_min(dd->queue, 4096);

	/*
	 * write back cache is not supported in the device. FUA depends on
	 * write back cache support, hence setting flush support to zero.
	 */
	blk_queue_flush(dd->queue, 0);

	/* Signal trim support */
	if (dd->trim_supp == true) {
		set_bit(QUEUE_FLAG_DISCARD, &dd->queue->queue_flags);
		dd->queue->limits.discard_granularity = 4096;
		blk_queue_max_discard_sectors(dd->queue,
			MTIP_MAX_TRIM_ENTRY_LEN * MTIP_MAX_TRIM_ENTRIES);
		dd->queue->limits.discard_zeroes_data = 0;
	}

	/* Set the capacity of the device in 512 byte sectors. */
	if (!(mtip_hw_get_capacity(dd, &capacity))) {
		dev_warn(&dd->pdev->dev,
			"Could not read drive capacity\n");
		rv = -EIO;
		goto read_capacity_error;
	}
	set_capacity(dd->disk, capacity);

	/* Enable the block device and add it to /dev */
	add_disk(dd->disk);

	/*
	 * Now that the disk is active, initialize any sysfs attributes
	 * managed by the protocol layer.
	 */
	kobj = kobject_get(&disk_to_dev(dd->disk)->kobj);
	if (kobj) {
		mtip_hw_sysfs_init(dd, kobj);
		kobject_put(kobj);
	}
	mtip_hw_debugfs_init(dd);

	if (dd->mtip_svc_handler) {
		set_bit(MTIP_DDF_INIT_DONE_BIT, &dd->dd_flag);
		return rv; /* service thread created for handling rebuild */
	}

start_service_thread:
	sprintf(thd_name, "mtip_svc_thd_%02d", index);

	dd->mtip_svc_handler = kthread_run(mtip_service_thread,
						dd, thd_name);

	if (IS_ERR(dd->mtip_svc_handler)) {
		dev_err(&dd->pdev->dev, "service thread failed to start\n");
		dd->mtip_svc_handler = NULL;
		rv = -EFAULT;
		goto kthread_run_error;
	}

	if (wait_for_rebuild == MTIP_FTL_REBUILD_MAGIC)
		rv = wait_for_rebuild;

	return rv;

kthread_run_error:
	mtip_hw_debugfs_exit(dd);

	/* Delete our gendisk. This also removes the device from /dev */
	del_gendisk(dd->disk);

read_capacity_error:
	blk_cleanup_queue(dd->queue);

block_queue_alloc_init_error:
disk_index_error:
	spin_lock(&rssd_index_lock);
	ida_remove(&rssd_index_ida, index);
	spin_unlock(&rssd_index_lock);

ida_get_error:
	put_disk(dd->disk);

alloc_disk_error:
	mtip_hw_exit(dd); /* De-initialize the protocol layer. */

protocol_init_error:
	return rv;
}