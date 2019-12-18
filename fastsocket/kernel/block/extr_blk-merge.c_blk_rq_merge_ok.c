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
struct request {scalar_t__ rq_disk; scalar_t__ special; TYPE_1__* bio; } ;
struct bio {int bi_rw; TYPE_2__* bi_bdev; } ;
struct TYPE_4__ {scalar_t__ bd_disk; } ;
struct TYPE_3__ {int bi_rw; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_mergeable (struct bio*) ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_mergeable (struct request*) ; 

bool blk_rq_merge_ok(struct request *rq, struct bio *bio)
{
	if (!rq_mergeable(rq) || !bio_mergeable(bio))
		return false;

	/* don't merge file system requests and discard requests */
	if ((bio->bi_rw & BIO_DISCARD) != (rq->bio->bi_rw & BIO_DISCARD))
		return false;

	/* different data direction or already started, don't merge */
	if (bio_data_dir(bio) != rq_data_dir(rq))
		return false;

	/* must be same device and not a special request */
	if (rq->rq_disk != bio->bi_bdev->bd_disk || rq->special)
		return false;

	/* only merge integrity protected bio into ditto rq */
	if (bio_integrity(bio) != blk_integrity_rq(rq))
		return false;

	return true;
}