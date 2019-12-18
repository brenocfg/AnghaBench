#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ head; } ;
struct r1conf {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  wait_barrier; TYPE_1__* mddev; scalar_t__ pending_count; int /*<<< orphan*/  plug; TYPE_2__ pending_bio_list; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_bdev; struct bio* bi_next; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 struct bio* bio_list_get (TYPE_2__*) ; 
 int /*<<< orphan*/  bitmap_unplug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  plugger_remove_plug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flush_pending_writes(struct r1conf *conf)
{
	/* Any writes that have been queued but are awaiting
	 * bitmap updates get flushed here.
	 * We return 1 if any requests were actually submitted.
	 */
	int rv = 0;

	spin_lock_irq(&conf->device_lock);

	if (conf->pending_bio_list.head) {
		struct bio *bio;
		bio = bio_list_get(&conf->pending_bio_list);
		plugger_remove_plug(&conf->plug);
		conf->pending_count = 0;
		spin_unlock_irq(&conf->device_lock);
		/* flush any pending bitmap writes to
		 * disk before proceeding w/ I/O */
		bitmap_unplug(conf->mddev->bitmap);
		wake_up(&conf->wait_barrier);

		while (bio) { /* submit pending writes */
			struct bio *next = bio->bi_next;
			bio->bi_next = NULL;
			if (unlikely((bio->bi_rw & BIO_DISCARD) &&
			    !blk_queue_discard(bdev_get_queue(bio->bi_bdev))))
				/* Just ignore it */
				bio_endio(bio, 0);
			else
				generic_make_request(bio);
			bio = next;
		}
		rv = 1;
	} else
		spin_unlock_irq(&conf->device_lock);
	return rv;
}