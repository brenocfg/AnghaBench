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
struct deadline_data {int dummy; } ;
struct TYPE_2__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 int ELEVATOR_FRONT_MERGE ; 
 int /*<<< orphan*/  deadline_add_rq_rb (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  deadline_rb_root (struct deadline_data*,struct request*) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void deadline_merged_request(struct request_queue *q,
				    struct request *req, int type)
{
	struct deadline_data *dd = q->elevator->elevator_data;

	/*
	 * if the merge was a front merge, we need to reposition request
	 */
	if (type == ELEVATOR_FRONT_MERGE) {
		elv_rb_del(deadline_rb_root(dd, req), req);
		deadline_add_rq_rb(dd, req);
	}
}