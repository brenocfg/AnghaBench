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
struct request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct cfq_queue {int /*<<< orphan*/  cfqd; TYPE_1__ fifo; } ;

/* Variables and functions */
 scalar_t__ cfq_cfqq_fifo_expire (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (int /*<<< orphan*/ ,struct cfq_queue*,char*,struct request*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_fifo_expire (struct cfq_queue*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ list_empty (TYPE_1__*) ; 
 struct request* rq_entry_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_fifo_time (struct request*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *cfq_check_fifo(struct cfq_queue *cfqq)
{
	struct request *rq = NULL;

	if (cfq_cfqq_fifo_expire(cfqq))
		return NULL;

	cfq_mark_cfqq_fifo_expire(cfqq);

	if (list_empty(&cfqq->fifo))
		return NULL;

	rq = rq_entry_fifo(cfqq->fifo.next);
	if (time_before(jiffies, rq_fifo_time(rq)))
		rq = NULL;

	cfq_log_cfqq(cfqq->cfqd, cfqq, "fifo=%p", rq);
	return rq;
}