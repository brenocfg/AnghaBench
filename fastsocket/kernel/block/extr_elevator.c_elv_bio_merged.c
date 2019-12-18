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
struct request {int dummy; } ;
struct elevator_queue {TYPE_1__* ops; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* elevator_bio_merged_fn ) (struct request_queue*,struct request*,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct request_queue*,struct request*,struct bio*) ; 

void elv_bio_merged(struct request_queue *q, struct request *rq,
			struct bio *bio)
{
	struct elevator_queue *e = q->elevator;

	if (e->ops->elevator_bio_merged_fn)
		e->ops->elevator_bio_merged_fn(q, rq, bio);
}