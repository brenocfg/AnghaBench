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
struct request_queue {struct request* last_merge; } ;
struct request {struct bio* biotail; int /*<<< orphan*/  cmd_flags; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_SEG_VALID ; 
 int /*<<< orphan*/  REQ_NOMERGE ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  blk_recount_segments (struct request_queue*,struct bio*) ; 
 scalar_t__ blk_rq_get_max_sectors (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int ll_new_hw_segment (struct request_queue*,struct request*,struct bio*) ; 

int ll_back_merge_fn(struct request_queue *q, struct request *req,
		     struct bio *bio)
{
	if (blk_rq_sectors(req) + bio_sectors(bio) >
	    blk_rq_get_max_sectors(req)) {
		req->cmd_flags |= REQ_NOMERGE;
		if (req == q->last_merge)
			q->last_merge = NULL;
		return 0;
	}
	if (!bio_flagged(req->biotail, BIO_SEG_VALID))
		blk_recount_segments(q, req->biotail);
	if (!bio_flagged(bio, BIO_SEG_VALID))
		blk_recount_segments(q, bio);

	return ll_new_hw_segment(q, req, bio);
}