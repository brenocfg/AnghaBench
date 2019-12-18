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
struct request {int cmd_flags; scalar_t__ rq_disk; int /*<<< orphan*/ * bio; int /*<<< orphan*/  cpu; int /*<<< orphan*/  ioprio; int /*<<< orphan*/  __data_len; TYPE_1__* biotail; int /*<<< orphan*/  start_time; scalar_t__ special; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bi_next; } ;

/* Variables and functions */
 int REQ_DISCARD ; 
 int REQ_FAILFAST_MASK ; 
 int REQ_MIXED_MERGE ; 
 int /*<<< orphan*/  __blk_put_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  blk_account_io_merge (struct request*) ; 
 scalar_t__ blk_integrity_rq (struct request*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_cpu_valid (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  blk_rq_set_mixed_merge (struct request*) ; 
 int /*<<< orphan*/  elv_merge_requests (struct request_queue*,struct request*,struct request*) ; 
 int /*<<< orphan*/  ioprio_best (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_merge_requests_fn (struct request_queue*,struct request*,struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_mergeable (struct request*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attempt_merge(struct request_queue *q, struct request *req,
			  struct request *next)
{
	if (!rq_mergeable(req) || !rq_mergeable(next))
		return 0;

	/*
	 * Don't merge file system requests and discard requests
	 */
	if ((req->cmd_flags & REQ_DISCARD) != (next->cmd_flags & REQ_DISCARD))
		return 0;

	/*
	 * not contiguous
	 */
	if (blk_rq_pos(req) + blk_rq_sectors(req) != blk_rq_pos(next))
		return 0;

	if (rq_data_dir(req) != rq_data_dir(next)
	    || req->rq_disk != next->rq_disk
	    || next->special)
		return 0;

	if (blk_integrity_rq(req) != blk_integrity_rq(next))
		return 0;

	/*
	 * If we are allowed to merge, then append bio list
	 * from next to rq and release next. merge_requests_fn
	 * will have updated segment counts, update sector
	 * counts here.
	 */
	if (!ll_merge_requests_fn(q, req, next))
		return 0;

	/*
	 * If failfast settings disagree or any of the two is already
	 * a mixed merge, mark both as mixed before proceeding.  This
	 * makes sure that all involved bios have mixable attributes
	 * set properly.
	 */
	if ((req->cmd_flags | next->cmd_flags) & REQ_MIXED_MERGE ||
	    (req->cmd_flags & REQ_FAILFAST_MASK) !=
	    (next->cmd_flags & REQ_FAILFAST_MASK)) {
		blk_rq_set_mixed_merge(req);
		blk_rq_set_mixed_merge(next);
	}

	/*
	 * At this point we have either done a back merge
	 * or front merge. We need the smaller start_time of
	 * the merged requests to be the current request
	 * for accounting purposes.
	 */
	if (time_after(req->start_time, next->start_time))
		req->start_time = next->start_time;

	req->biotail->bi_next = next->bio;
	req->biotail = next->biotail;

	req->__data_len += blk_rq_bytes(next);

	elv_merge_requests(q, req, next);

	/*
	 * 'next' is going away, so update stats accordingly
	 */
	blk_account_io_merge(next);

	req->ioprio = ioprio_best(req->ioprio, next->ioprio);
	if (blk_rq_cpu_valid(next))
		req->cpu = next->cpu;

	/* owner-ship of bio passed from next to req */
	next->bio = NULL;
	__blk_put_request(q, next);
	return 1;
}