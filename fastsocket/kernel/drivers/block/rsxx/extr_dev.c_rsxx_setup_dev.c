#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_17__ {unsigned short block_size; } ;
struct TYPE_18__ {TYPE_1__ data; } ;
struct rsxx_cardinfo {scalar_t__ major; int disk_id; TYPE_5__* queue; TYPE_15__* gendisk; TYPE_4__* dev; TYPE_2__ config; int /*<<< orphan*/  dev_lock; } ;
struct TYPE_19__ {int discard_granularity; int discard_alignment; int discard_zeroes_data; } ;
struct TYPE_21__ {struct rsxx_cardinfo* queuedata; TYPE_3__ limits; } ;
struct TYPE_20__ {int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {scalar_t__ major; TYPE_5__* queue; struct rsxx_cardinfo* private_data; int /*<<< orphan*/ * fops; scalar_t__ first_minor; int /*<<< orphan*/ * driverfs_dev; int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_ANY ; 
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int RSXX_HW_BLK_SIZE ; 
 TYPE_15__* alloc_disk (int /*<<< orphan*/ ) ; 
 TYPE_5__* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (TYPE_5__*,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_5__*,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_make_request (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (TYPE_5__*,int) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (TYPE_5__*,int) ; 
 int /*<<< orphan*/  blkdev_max_hw_sectors ; 
 int /*<<< orphan*/  blkdev_minors ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  enable_blkdev ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ register_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rsxx_discard_supported (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_fops ; 
 int /*<<< orphan*/  rsxx_make_request ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  unregister_blkdev (scalar_t__,int /*<<< orphan*/ ) ; 

int rsxx_setup_dev(struct rsxx_cardinfo *card)
{
	unsigned short blk_size;

	mutex_init(&card->dev_lock);

	if (!enable_blkdev)
		return 0;

	card->major = register_blkdev(0, DRIVER_NAME);
	if (card->major < 0) {
		dev_err(CARD_TO_DEV(card), "Failed to get major number\n");
		return -ENOMEM;
	}

	card->queue = blk_alloc_queue(GFP_KERNEL);
	if (!card->queue) {
		dev_err(CARD_TO_DEV(card), "Failed queue alloc\n");
		unregister_blkdev(card->major, DRIVER_NAME);
		return -ENOMEM;
	}

	card->gendisk = alloc_disk(blkdev_minors);
	if (!card->gendisk) {
		dev_err(CARD_TO_DEV(card), "Failed disk alloc\n");
		blk_cleanup_queue(card->queue);
		unregister_blkdev(card->major, DRIVER_NAME);
		return -ENOMEM;
	}

	blk_size = card->config.data.block_size;

	blk_queue_make_request(card->queue, rsxx_make_request);
	blk_queue_bounce_limit(card->queue, BLK_BOUNCE_ANY);
	blk_queue_dma_alignment(card->queue, blk_size - 1);
	blk_queue_max_hw_sectors(card->queue, blkdev_max_hw_sectors);
	blk_queue_logical_block_size(card->queue, blk_size);
	blk_queue_physical_block_size(card->queue, RSXX_HW_BLK_SIZE);

	queue_flag_set_unlocked(QUEUE_FLAG_NONROT, card->queue);
	if (rsxx_discard_supported(card)) {
		queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, card->queue);
		blk_queue_max_discard_sectors(card->queue,
						RSXX_HW_BLK_SIZE >> 9);
		card->queue->limits.discard_granularity = RSXX_HW_BLK_SIZE;
		card->queue->limits.discard_alignment   = RSXX_HW_BLK_SIZE;
		card->queue->limits.discard_zeroes_data = 1;
	}

	card->queue->queuedata = card;

	snprintf(card->gendisk->disk_name, sizeof(card->gendisk->disk_name),
		 "rsxx%d", card->disk_id);
	card->gendisk->driverfs_dev = &card->dev->dev;
	card->gendisk->major = card->major;
	card->gendisk->first_minor = 0;
	card->gendisk->fops = &rsxx_fops;
	card->gendisk->private_data = card;
	card->gendisk->queue = card->queue;

	return 0;
}