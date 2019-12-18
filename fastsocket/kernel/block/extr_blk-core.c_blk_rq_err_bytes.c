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
struct request {unsigned int cmd_flags; struct bio* bio; } ;
struct bio {unsigned int bi_rw; scalar_t__ bi_size; struct bio* bi_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int REQ_FAILFAST_MASK ; 
 int REQ_MIXED_MERGE ; 
 unsigned int blk_rq_bytes (struct request const*) ; 

unsigned int blk_rq_err_bytes(const struct request *rq)
{
	unsigned int ff = rq->cmd_flags & REQ_FAILFAST_MASK;
	unsigned int bytes = 0;
	struct bio *bio;

	if (!(rq->cmd_flags & REQ_MIXED_MERGE))
		return blk_rq_bytes(rq);

	/*
	 * Currently the only 'mixing' which can happen is between
	 * different fastfail types.  We can safely fail portions
	 * which have all the failfast bits that the first one has -
	 * the ones which are at least as eager to fail as the first
	 * one.
	 */
	for (bio = rq->bio; bio; bio = bio->bi_next) {
		if ((bio->bi_rw & ff) != ff)
			break;
		bytes += bio->bi_size;
	}

	/* this could lead to infinite loop */
	BUG_ON(blk_rq_bytes(rq) && !bytes);
	return bytes;
}