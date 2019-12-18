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
struct request_queue {int dummy; } ;
struct request {struct bio* bio; } ;
struct bio {int /*<<< orphan*/  bi_flags; int /*<<< orphan*/  bi_size; } ;
struct TYPE_2__ {struct request* rq; } ;
struct aoedev {TYPE_1__ ip; struct request_queue* blkq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ __blk_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blk_run_queue (struct request_queue*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
aoe_end_request(struct aoedev *d, struct request *rq, int fastfail)
{
	struct bio *bio;
	int bok;
	struct request_queue *q;

	q = d->blkq;
	if (rq == d->ip.rq)
		d->ip.rq = NULL;
	do {
		bio = rq->bio;
		bok = !fastfail && test_bit(BIO_UPTODATE, &bio->bi_flags);
	} while (__blk_end_request(rq, bok ? 0 : -EIO, bio->bi_size));

	/* cf. http://lkml.org/lkml/2006/10/31/28 */
	if (!fastfail)
		__blk_run_queue(q);
}