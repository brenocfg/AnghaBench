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
struct request {struct request_queue* q; } ;
struct elevator_queue {TYPE_1__* ops; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int (* elevator_allow_merge_fn ) (struct request_queue*,struct request*,struct bio*) ;} ;

/* Variables and functions */
 int stub1 (struct request_queue*,struct request*,struct bio*) ; 

__attribute__((used)) static int elv_iosched_allow_merge(struct request *rq, struct bio *bio)
{
	struct request_queue *q = rq->q;
	struct elevator_queue *e = q->elevator;

	if (e->ops->elevator_allow_merge_fn)
		return e->ops->elevator_allow_merge_fn(q, rq, bio);

	return 1;
}