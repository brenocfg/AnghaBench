#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  expires; } ;
struct request_queue {TYPE_1__ timeout; int /*<<< orphan*/  timeout_list; scalar_t__ rq_timeout; int /*<<< orphan*/  rq_timed_out_fn; } ;
struct request {scalar_t__ deadline; int /*<<< orphan*/  timeout_list; scalar_t__ timeout; int /*<<< orphan*/  atomic_flags; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  REQ_ATOM_COMPLETE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 unsigned long round_jiffies_up (scalar_t__) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void blk_add_timer(struct request *req)
{
	struct request_queue *q = req->q;
	unsigned long expiry;

	if (!q->rq_timed_out_fn)
		return;

	BUG_ON(!list_empty(&req->timeout_list));
	BUG_ON(test_bit(REQ_ATOM_COMPLETE, &req->atomic_flags));

	/*
	 * Some LLDs, like scsi, peek at the timeout to prevent a
	 * command from being retried forever.
	 */
	if (!req->timeout)
		req->timeout = q->rq_timeout;

	req->deadline = jiffies + req->timeout;
	list_add_tail(&req->timeout_list, &q->timeout_list);

	/*
	 * If the timer isn't already pending or this timeout is earlier
	 * than an existing one, modify the timer. Round up to next nearest
	 * second.
	 */
	expiry = round_jiffies_up(req->deadline);

	if (!timer_pending(&q->timeout) ||
	    time_before(expiry, q->timeout.expires))
		mod_timer(&q->timeout, expiry);
}