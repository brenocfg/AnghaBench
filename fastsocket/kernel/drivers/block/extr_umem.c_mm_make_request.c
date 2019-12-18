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
struct request_queue {struct cardinfo* queuedata; } ;
struct cardinfo {int /*<<< orphan*/  lock; struct bio** biotail; } ;
struct bio {struct bio* bi_next; int /*<<< orphan*/  bi_size; scalar_t__ bi_sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mm_make_request(struct request_queue *q, struct bio *bio)
{
	struct cardinfo *card = q->queuedata;
	pr_debug("mm_make_request %llu %u\n",
		 (unsigned long long)bio->bi_sector, bio->bi_size);

	spin_lock_irq(&card->lock);
	*card->biotail = bio;
	bio->bi_next = NULL;
	card->biotail = &bio->bi_next;
	blk_plug_device(q);
	spin_unlock_irq(&card->lock);

	return 0;
}