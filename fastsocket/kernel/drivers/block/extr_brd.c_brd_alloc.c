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
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  flags; scalar_t__ queue; struct brd_device* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
struct brd_device {int brd_number; scalar_t__ brd_queue; struct gendisk* brd_disk; int /*<<< orphan*/  brd_pages; int /*<<< orphan*/  brd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_ANY ; 
 int /*<<< orphan*/  GENHD_FL_SUPPRESS_PARTITION_INFO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAMDISK_MAJOR ; 
 struct gendisk* alloc_disk (int) ; 
 scalar_t__ blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_make_request (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (scalar_t__,int) ; 
 int /*<<< orphan*/  brd_fops ; 
 int /*<<< orphan*/  brd_make_request ; 
 int /*<<< orphan*/  kfree (struct brd_device*) ; 
 struct brd_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int part_shift ; 
 int rd_size ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct brd_device *brd_alloc(int i)
{
	struct brd_device *brd;
	struct gendisk *disk;

	brd = kzalloc(sizeof(*brd), GFP_KERNEL);
	if (!brd)
		goto out;
	brd->brd_number		= i;
	spin_lock_init(&brd->brd_lock);
	INIT_RADIX_TREE(&brd->brd_pages, GFP_ATOMIC);

	brd->brd_queue = blk_alloc_queue(GFP_KERNEL);
	if (!brd->brd_queue)
		goto out_free_dev;
	blk_queue_make_request(brd->brd_queue, brd_make_request);
	blk_queue_max_hw_sectors(brd->brd_queue, 1024);
	blk_queue_bounce_limit(brd->brd_queue, BLK_BOUNCE_ANY);

	disk = brd->brd_disk = alloc_disk(1 << part_shift);
	if (!disk)
		goto out_free_queue;
	disk->major		= RAMDISK_MAJOR;
	disk->first_minor	= i << part_shift;
	disk->fops		= &brd_fops;
	disk->private_data	= brd;
	disk->queue		= brd->brd_queue;
	disk->flags |= GENHD_FL_SUPPRESS_PARTITION_INFO;
	sprintf(disk->disk_name, "ram%d", i);
	set_capacity(disk, rd_size * 2);

	return brd;

out_free_queue:
	blk_cleanup_queue(brd->brd_queue);
out_free_dev:
	kfree(brd);
out:
	return NULL;
}