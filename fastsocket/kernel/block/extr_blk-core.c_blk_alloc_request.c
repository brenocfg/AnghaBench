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
struct request {unsigned int cmd_flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned int REQ_ALLOCED ; 
 unsigned int REQ_ELVPRIV ; 
 int /*<<< orphan*/  blk_rq_init (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  elv_set_request (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 
 struct request* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *
blk_alloc_request(struct request_queue *q, unsigned int flags, gfp_t gfp_mask)
{
	struct request *rq = mempool_alloc(q->rq.rq_pool, gfp_mask);

	if (!rq)
		return NULL;

	blk_rq_init(q, rq);

	rq->cmd_flags = flags | REQ_ALLOCED;

	if ((flags & REQ_ELVPRIV) &&
	    unlikely(elv_set_request(q, rq, gfp_mask))) {
		mempool_free(rq, q->rq.rq_pool);
		return NULL;
	}

	return rq;
}