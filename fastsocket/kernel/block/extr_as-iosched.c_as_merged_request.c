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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct as_data {int dummy; } ;
struct TYPE_2__ {struct as_data* elevator_data; } ;

/* Variables and functions */
 int ELEVATOR_FRONT_MERGE ; 
 int /*<<< orphan*/  RQ_RB_ROOT (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  as_del_rq_rb (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rb_add (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void as_merged_request(struct request_queue *q, struct request *req,
			      int type)
{
	struct as_data *ad = q->elevator->elevator_data;

	/*
	 * if the merge was a front merge, we need to reposition request
	 */
	if (type == ELEVATOR_FRONT_MERGE) {
		as_del_rq_rb(ad, req);
		elv_rb_add(RQ_RB_ROOT(ad, req), req);
		/*
		 * Note! At this stage of this and the next function, our next
		 * request may not be optimal - eg the request may have "grown"
		 * behind the disk head. We currently don't bother adjusting.
		 */
	}
}