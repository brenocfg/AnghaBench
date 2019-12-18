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
struct request {void* special; struct bio* bio; } ;
struct buf {int dummy; } ;
struct bio {struct bio* bi_next; } ;
struct TYPE_2__ {struct buf* buf; struct request* rq; struct bio* nxbio; } ;
struct aoedev {TYPE_1__ ip; int /*<<< orphan*/  bufpool; struct request_queue* blkq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  bufinit (struct buf*,struct request*,struct bio*) ; 
 struct buf* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ rqbiocnt (struct request*) ; 

__attribute__((used)) static struct buf *
nextbuf(struct aoedev *d)
{
	struct request *rq;
	struct request_queue *q;
	struct buf *buf;
	struct bio *bio;

	q = d->blkq;
	if (q == NULL)
		return NULL;	/* initializing */
	if (d->ip.buf)
		return d->ip.buf;
	rq = d->ip.rq;
	if (rq == NULL) {
		rq = blk_peek_request(q);
		if (rq == NULL)
			return NULL;
		blk_start_request(rq);
		d->ip.rq = rq;
		d->ip.nxbio = rq->bio;
		rq->special = (void *) rqbiocnt(rq);
	}
	buf = mempool_alloc(d->bufpool, GFP_ATOMIC);
	if (buf == NULL) {
		pr_err("aoe: nextbuf: unable to mempool_alloc!\n");
		return NULL;
	}
	bio = d->ip.nxbio;
	bufinit(buf, rq, bio);
	bio = bio->bi_next;
	d->ip.nxbio = bio;
	if (bio == NULL)
		d->ip.rq = NULL;
	return d->ip.buf = buf;
}