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
typedef  int u64 ;
struct rsxx_cardinfo {int /*<<< orphan*/  halt; int /*<<< orphan*/  dma_fault; int /*<<< orphan*/  gendisk; } ;
struct rsxx_bio_meta {int /*<<< orphan*/  pending_dmas; int /*<<< orphan*/  start_time; int /*<<< orphan*/  error; struct bio* bio; } ;
struct request_queue {struct rsxx_cardinfo* queuedata; } ;
struct bio {scalar_t__ bi_sector; int bi_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_dma_done_cb ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int) ; 
 int /*<<< orphan*/  bio_meta_pool ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char,struct rsxx_bio_meta*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_stats_start (struct rsxx_cardinfo*,struct bio*) ; 
 scalar_t__ get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct rsxx_bio_meta* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rsxx_bio_meta*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int rsxx_dma_queue_bio (struct rsxx_cardinfo*,struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rsxx_bio_meta*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsxx_make_request(struct request_queue *q, struct bio *bio)
{
	struct rsxx_cardinfo *card = q->queuedata;
	struct rsxx_bio_meta *bio_meta;
	int st = -EINVAL;

	might_sleep();

	if (!card)
		goto req_err;

	if (bio->bi_sector + (bio->bi_size >> 9) > get_capacity(card->gendisk))
		goto req_err;

	if (unlikely(card->halt)) {
		st = -EFAULT;
		goto req_err;
	}

	if (unlikely(card->dma_fault)) {
		st = (-EFAULT);
		goto req_err;
	}

	if (bio->bi_size == 0) {
		dev_err(CARD_TO_DEV(card), "size zero BIO!\n");
		goto req_err;
	}

	bio_meta = kmem_cache_alloc(bio_meta_pool, GFP_KERNEL);
	if (!bio_meta) {
		st = -ENOMEM;
		goto req_err;
	}

	bio_meta->bio = bio;
	atomic_set(&bio_meta->error, 0);
	atomic_set(&bio_meta->pending_dmas, 0);
	bio_meta->start_time = jiffies;

	if (!unlikely(card->halt))
		disk_stats_start(card, bio);

	dev_dbg(CARD_TO_DEV(card), "BIO[%c]: meta: %p addr8: x%llx size: %d\n",
		 bio_data_dir(bio) ? 'W' : 'R', bio_meta,
		 (u64)bio->bi_sector << 9, bio->bi_size);

	st = rsxx_dma_queue_bio(card, bio, &bio_meta->pending_dmas,
				    bio_dma_done_cb, bio_meta);
	if (st)
		goto queue_err;

	return 0;

queue_err:
	kmem_cache_free(bio_meta_pool, bio_meta);
req_err:
	bio_endio(bio, st);

	return 0;
}