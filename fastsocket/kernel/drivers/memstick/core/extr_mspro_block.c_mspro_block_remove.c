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
struct mspro_block_data {int eject; int /*<<< orphan*/  disk; int /*<<< orphan*/  attr_group; int /*<<< orphan*/ * queue; int /*<<< orphan*/  q_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct memstick_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_start_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  memstick_set_drvdata (struct memstick_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mspro_block_data_clear (struct mspro_block_data*) ; 
 int /*<<< orphan*/  mspro_block_disk_lock ; 
 int /*<<< orphan*/  mspro_block_disk_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mspro_block_remove(struct memstick_dev *card)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);
	unsigned long flags;

	del_gendisk(msb->disk);
	dev_dbg(&card->dev, "mspro block remove\n");
	spin_lock_irqsave(&msb->q_lock, flags);
	msb->eject = 1;
	blk_start_queue(msb->queue);
	spin_unlock_irqrestore(&msb->q_lock, flags);

	blk_cleanup_queue(msb->queue);
	msb->queue = NULL;

	sysfs_remove_group(&card->dev.kobj, &msb->attr_group);

	mutex_lock(&mspro_block_disk_lock);
	mspro_block_data_clear(msb);
	mutex_unlock(&mspro_block_disk_lock);

	mspro_block_disk_release(msb->disk);
	memstick_set_drvdata(card, NULL);
}