#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct driver_data {int /*<<< orphan*/  index; int /*<<< orphan*/ * queue; TYPE_2__* disk; TYPE_1__* pdev; } ;
struct TYPE_5__ {scalar_t__ queue; int /*<<< orphan*/  disk_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_hw_shutdown (struct driver_data*) ; 
 int /*<<< orphan*/  put_disk (TYPE_2__*) ; 
 int /*<<< orphan*/  rssd_index_ida ; 
 int /*<<< orphan*/  rssd_index_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtip_block_shutdown(struct driver_data *dd)
{
	/* Delete our gendisk structure, and cleanup the blk queue. */
	if (dd->disk) {
		dev_info(&dd->pdev->dev,
			"Shutting down %s ...\n", dd->disk->disk_name);

		if (dd->disk->queue) {
			del_gendisk(dd->disk);
			blk_cleanup_queue(dd->queue);
		} else
			put_disk(dd->disk);
		dd->disk  = NULL;
		dd->queue = NULL;
	}

	spin_lock(&rssd_index_lock);
	ida_remove(&rssd_index_ida, dd->index);
	spin_unlock(&rssd_index_lock);

	mtip_hw_shutdown(dd);
	return 0;
}