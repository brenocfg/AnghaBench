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
struct request {void* special; } ;
struct bio {struct bio* bi_next; int /*<<< orphan*/  bi_flags; } ;
struct TYPE_2__ {struct bio* nxbio; struct request* rq; int /*<<< orphan*/  buf; } ;
struct aoedev {TYPE_1__ ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int /*<<< orphan*/  aoe_end_request (struct aoedev*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aoe_failbuf (struct aoedev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aoe_failip(struct aoedev *d)
{
	struct request *rq;
	struct bio *bio;
	unsigned long n;

	aoe_failbuf(d, d->ip.buf);

	rq = d->ip.rq;
	if (rq == NULL)
		return;
	while ((bio = d->ip.nxbio)) {
		clear_bit(BIO_UPTODATE, &bio->bi_flags);
		d->ip.nxbio = bio->bi_next;
		n = (unsigned long) rq->special;
		rq->special = (void *) --n;
	}
	if ((unsigned long) rq->special == 0)
		aoe_end_request(d, rq, 0);
}