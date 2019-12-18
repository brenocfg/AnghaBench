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
struct request {int /*<<< orphan*/ ** elevator_private; } ;
struct cfq_queue {int /*<<< orphan*/ * allocated; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 TYPE_1__* RQ_CIC (struct request*) ; 
 int /*<<< orphan*/  cfq_put_cfqg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  put_io_context (int /*<<< orphan*/ ) ; 
 int rq_data_dir (struct request*) ; 

__attribute__((used)) static void cfq_put_request(struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	if (cfqq) {
		const int rw = rq_data_dir(rq);

		BUG_ON(!cfqq->allocated[rw]);
		cfqq->allocated[rw]--;

		put_io_context(RQ_CIC(rq)->ioc);

		rq->elevator_private[0] = NULL;
		rq->elevator_private[1] = NULL;

		/* Put down rq reference on cfqg */
		cfq_put_cfqg(RQ_CFQG(rq));
		rq->elevator_private[2] = NULL;

		cfq_put_queue(cfqq);
	}
}