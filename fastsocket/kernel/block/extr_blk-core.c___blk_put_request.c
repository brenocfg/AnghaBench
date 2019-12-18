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
struct request {int ref_count; int cmd_flags; int /*<<< orphan*/  hash; int /*<<< orphan*/  queuelist; int /*<<< orphan*/ * bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int REQ_ALLOCED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_free_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  elv_completed_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  freed_request (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void __blk_put_request(struct request_queue *q, struct request *req)
{
	if (unlikely(!q))
		return;
	if (unlikely(--req->ref_count))
		return;

	elv_completed_request(q, req);

	/* this is a bio leak */
	WARN_ON(req->bio != NULL);

	/*
	 * Request may not have originated from ll_rw_blk. if not,
	 * it didn't come out of our reserved rq pools
	 */
	if (req->cmd_flags & REQ_ALLOCED) {
		unsigned int flags = req->cmd_flags;

		BUG_ON(!list_empty(&req->queuelist));
		BUG_ON(!hlist_unhashed(&req->hash));

		blk_free_request(q, req);
		freed_request(q, flags);
	}
}