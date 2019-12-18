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
struct cfq_queue {TYPE_1__* cfqd; int /*<<< orphan*/  fifo; scalar_t__ next_rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __cfq_slice_expired (TYPE_1__*,struct cfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_dispatch_insert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __cfq_forced_dispatch_cfqq(struct cfq_queue *cfqq)
{
	int dispatched = 0;

	while (cfqq->next_rq) {
		cfq_dispatch_insert(cfqq->cfqd->queue, cfqq->next_rq);
		dispatched++;
	}

	BUG_ON(!list_empty(&cfqq->fifo));

	/* By default cfqq is not expired if it is empty. Do it explicitly */
	__cfq_slice_expired(cfqq->cfqd, cfqq, 0);
	return dispatched;
}