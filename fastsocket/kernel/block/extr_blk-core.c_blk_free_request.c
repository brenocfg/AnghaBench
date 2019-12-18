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
struct TYPE_2__ {int /*<<< orphan*/  rq_pool; } ;
struct request_queue {TYPE_1__ rq; } ;
struct request {int cmd_flags; } ;

/* Variables and functions */
 int REQ_ELVPRIV ; 
 int /*<<< orphan*/  elv_put_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  mempool_free (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void blk_free_request(struct request_queue *q, struct request *rq)
{
	if (rq->cmd_flags & REQ_ELVPRIV)
		elv_put_request(q, rq);
	mempool_free(rq, q->rq.rq_pool);
}