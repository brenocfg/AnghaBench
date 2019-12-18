#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_2__* elevator; } ;
struct request {int /*<<< orphan*/  queuelist; } ;
struct cfq_queue {int /*<<< orphan*/  fifo; } ;
struct cfq_data {TYPE_1__* serving_group; scalar_t__* cfq_fifo_expire; } ;
struct TYPE_8__ {int /*<<< orphan*/  blkg; } ;
struct TYPE_7__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_6__ {struct cfq_data* elevator_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  blkg; } ;

/* Variables and functions */
 TYPE_4__* RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 TYPE_3__* RQ_CIC (struct request*) ; 
 int /*<<< orphan*/  cfq_add_rq_rb (struct request*) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_io_add_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cfq_init_prio_data (struct cfq_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_rq_enqueued (struct cfq_data*,struct cfq_queue*,struct request*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 size_t rq_is_sync (struct request*) ; 
 int /*<<< orphan*/  rq_set_fifo_time (struct request*,scalar_t__) ; 

__attribute__((used)) static void cfq_insert_request(struct request_queue *q, struct request *rq)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	cfq_log_cfqq(cfqd, cfqq, "insert_request");
	cfq_init_prio_data(cfqq, RQ_CIC(rq)->ioc);

	rq_set_fifo_time(rq, jiffies + cfqd->cfq_fifo_expire[rq_is_sync(rq)]);
	list_add_tail(&rq->queuelist, &cfqq->fifo);
	cfq_add_rq_rb(rq);
	cfq_blkiocg_update_io_add_stats(&(RQ_CFQG(rq))->blkg,
			&cfqd->serving_group->blkg, rq_data_dir(rq),
			rq_is_sync(rq));
	cfq_rq_enqueued(cfqd, cfqq, rq);
}