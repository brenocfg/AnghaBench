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
struct request_queue {int /*<<< orphan*/  (* unprep_rq_fn ) (struct request_queue*,struct request*) ;} ;
struct request {int /*<<< orphan*/  cmd_flags; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_DONTPREP ; 
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*) ; 

void blk_unprep_request(struct request *req)
{
	struct request_queue *q = req->q;

	req->cmd_flags &= ~REQ_DONTPREP;
	if (q->unprep_rq_fn)
		q->unprep_rq_fn(q, req);
}