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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  __data_len; struct bio* biotail; int /*<<< orphan*/  bio; } ;
struct bio {scalar_t__ bi_size; struct bio* bi_next; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  blk_rq_bio_prep (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  ll_back_merge_fn (struct request_queue*,struct request*,struct bio*) ; 

int blk_rq_append_bio(struct request_queue *q, struct request *rq,
		      struct bio *bio)
{
	if (!rq->bio)
		blk_rq_bio_prep(q, rq, bio);
	else if (!ll_back_merge_fn(q, rq, bio))
		return -EINVAL;
	else {
		rq->biotail->bi_next = bio;
		rq->biotail = bio;

		rq->__data_len += bio->bi_size;
	}
	return 0;
}