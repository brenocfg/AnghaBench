#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct loop_device {int lo_number; TYPE_1__* lo_queue; int /*<<< orphan*/  lo_lock; int /*<<< orphan*/  lo_event; int /*<<< orphan*/ * lo_thread; int /*<<< orphan*/  lo_ctl_mutex; struct gendisk* lo_disk; int /*<<< orphan*/  lo_state; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; TYPE_1__* queue; struct loop_device* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
struct TYPE_4__ {struct loop_device* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOOP_MAJOR ; 
 int /*<<< orphan*/  Lo_unbound ; 
 struct gendisk* alloc_disk (int) ; 
 TYPE_1__* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_queue_make_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct loop_device*) ; 
 struct loop_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lo_fops ; 
 int /*<<< orphan*/  loop_make_request ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int part_shift ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct loop_device *loop_alloc(int i)
{
	struct loop_device *lo;
	struct gendisk *disk;

	lo = kzalloc(sizeof(*lo), GFP_KERNEL);
	if (!lo)
		goto out;

	lo->lo_state = Lo_unbound;

	lo->lo_queue = blk_alloc_queue(GFP_KERNEL);
	if (!lo->lo_queue)
		goto out_free_dev;

	/*
	 * set queue make_request_fn
	 */
	blk_queue_make_request(lo->lo_queue, loop_make_request);
	lo->lo_queue->queuedata = lo;

	disk = lo->lo_disk = alloc_disk(1 << part_shift);
	if (!disk)
		goto out_free_queue;

	mutex_init(&lo->lo_ctl_mutex);
	lo->lo_number		= i;
	lo->lo_thread		= NULL;
	init_waitqueue_head(&lo->lo_event);
	spin_lock_init(&lo->lo_lock);
	disk->major		= LOOP_MAJOR;
	disk->first_minor	= i << part_shift;
	disk->fops		= &lo_fops;
	disk->private_data	= lo;
	disk->queue		= lo->lo_queue;
	sprintf(disk->disk_name, "loop%d", i);
	return lo;

out_free_queue:
	blk_cleanup_queue(lo->lo_queue);
out_free_dev:
	kfree(lo);
out:
	return NULL;
}