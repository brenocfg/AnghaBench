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
struct request {scalar_t__ cmd_type; int cmd_flags; int /*<<< orphan*/  q; struct request* next_rq; int /*<<< orphan*/  (* end_io ) (struct request*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int REQ_DONTPREP ; 
 scalar_t__ REQ_TYPE_FS ; 
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  blk_account_io_done (struct request*) ; 
 scalar_t__ blk_bidi_rq (struct request*) ; 
 int /*<<< orphan*/  blk_delete_timer (struct request*) ; 
 int /*<<< orphan*/  blk_queue_end_tag (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  blk_queued_rq (struct request*) ; 
 scalar_t__ blk_rq_tagged (struct request*) ; 
 int /*<<< orphan*/  blk_unprep_request (struct request*) ; 
 int /*<<< orphan*/  laptop_io_completion () ; 
 int /*<<< orphan*/  laptop_mode ; 
 int /*<<< orphan*/  stub1 (struct request*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blk_finish_request(struct request *req, int error)
{
	if (blk_rq_tagged(req))
		blk_queue_end_tag(req->q, req);

	BUG_ON(blk_queued_rq(req));

	if (unlikely(laptop_mode) && req->cmd_type == REQ_TYPE_FS)
		laptop_io_completion();

	blk_delete_timer(req);

	if (req->cmd_flags & REQ_DONTPREP)
		blk_unprep_request(req);


	blk_account_io_done(req);

	if (req->end_io)
		req->end_io(req, error);
	else {
		if (blk_bidi_rq(req))
			__blk_put_request(req->next_rq->q, req->next_rq);

		__blk_put_request(req->q, req);
	}
}