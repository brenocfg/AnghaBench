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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct cfq_queue {int dummy; } ;

/* Variables and functions */
 int ELEVATOR_FRONT_MERGE ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 int /*<<< orphan*/  cfq_reposition_rq_rb (struct cfq_queue*,struct request*) ; 

__attribute__((used)) static void cfq_merged_request(struct request_queue *q, struct request *req,
			       int type)
{
	if (type == ELEVATOR_FRONT_MERGE) {
		struct cfq_queue *cfqq = RQ_CFQQ(req);

		cfq_reposition_rq_rb(cfqq, req);
	}
}