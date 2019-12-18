#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {int /*<<< orphan*/  queue; TYPE_1__* disk; scalar_t__ bs; scalar_t__ io_pool; scalar_t__ tio_pool; int /*<<< orphan*/  wq; int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  _minor_lock ; 
 int /*<<< orphan*/  bdput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioset_free (scalar_t__) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_integrity_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_devt (TYPE_1__*) ; 
 int /*<<< orphan*/  free_minor (int) ; 
 int /*<<< orphan*/  kfree (struct mapped_device*) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_fs (struct mapped_device*) ; 

__attribute__((used)) static void free_dev(struct mapped_device *md)
{
	int minor = MINOR(disk_devt(md->disk));

	unlock_fs(md);
	bdput(md->bdev);
	destroy_workqueue(md->wq);
	if (md->tio_pool)
		mempool_destroy(md->tio_pool);
	if (md->io_pool)
		mempool_destroy(md->io_pool);
	if (md->bs)
		bioset_free(md->bs);
	blk_integrity_unregister(md->disk);
	del_gendisk(md->disk);
	free_minor(minor);

	spin_lock(&_minor_lock);
	md->disk->private_data = NULL;
	spin_unlock(&_minor_lock);

	put_disk(md->disk);
	blk_cleanup_queue(md->queue);
	module_put(THIS_MODULE);
	kfree(md);
}