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
struct request_queue {struct elevator_queue* elevator; } ;
struct request {int /*<<< orphan*/ ** elevator_private; } ;
struct elevator_queue {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int (* elevator_set_req_fn ) (struct request_queue*,struct request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct request_queue*,struct request*,int /*<<< orphan*/ ) ; 

int elv_set_request(struct request_queue *q, struct request *rq, gfp_t gfp_mask)
{
	struct elevator_queue *e = q->elevator;

	if (e->ops->elevator_set_req_fn)
		return e->ops->elevator_set_req_fn(q, rq, gfp_mask);

	rq->elevator_private[0] = NULL;
	return 0;
}