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
struct bio {int bi_flags; struct bio* bi_next; int /*<<< orphan*/  bi_phys_segments; } ;

/* Variables and functions */
 int BIO_SEG_VALID ; 
 int /*<<< orphan*/  __blk_recalc_rq_segments (struct request_queue*,struct bio*) ; 

void blk_recount_segments(struct request_queue *q, struct bio *bio)
{
	struct bio *nxt = bio->bi_next;

	bio->bi_next = NULL;
	bio->bi_phys_segments = __blk_recalc_rq_segments(q, bio);
	bio->bi_next = nxt;
	bio->bi_flags |= (1 << BIO_SEG_VALID);
}