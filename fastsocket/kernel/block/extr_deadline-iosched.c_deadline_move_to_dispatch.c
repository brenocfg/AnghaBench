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
struct request {struct request_queue* q; } ;
struct deadline_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  deadline_remove_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  elv_dispatch_add_tail (struct request_queue*,struct request*) ; 

__attribute__((used)) static inline void
deadline_move_to_dispatch(struct deadline_data *dd, struct request *rq)
{
	struct request_queue *q = rq->q;

	deadline_remove_request(q, rq);
	elv_dispatch_add_tail(q, rq);
}