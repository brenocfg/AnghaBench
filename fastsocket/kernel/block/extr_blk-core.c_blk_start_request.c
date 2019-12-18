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
struct request {struct request* next_rq; void* resid_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_add_timer (struct request*) ; 
 int /*<<< orphan*/  blk_bidi_rq (struct request*) ; 
 int /*<<< orphan*/  blk_dequeue_request (struct request*) ; 
 void* blk_rq_bytes (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void blk_start_request(struct request *req)
{
	blk_dequeue_request(req);

	/*
	 * We are now handing the request to the hardware, initialize
	 * resid_len to full count and add the timeout handler.
	 */
	req->resid_len = blk_rq_bytes(req);
	if (unlikely(blk_bidi_rq(req)))
		req->next_rq->resid_len = blk_rq_bytes(req->next_rq);

	blk_add_timer(req);
}