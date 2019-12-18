#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_2__* elevator; } ;
struct request {int dummy; } ;
struct cfq_queue {TYPE_1__* cfqg; int /*<<< orphan*/  nr_sectors; int /*<<< orphan*/  dispatched; int /*<<< orphan*/  next_rq; } ;
struct cfq_data {int /*<<< orphan*/ * rq_in_flight; } ;
struct TYPE_6__ {int /*<<< orphan*/  dispatched; } ;
struct TYPE_5__ {struct cfq_data* elevator_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  blkg; } ;

/* Variables and functions */
 TYPE_3__* RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_dispatch_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_find_next_rq (struct cfq_data*,struct cfq_queue*,struct request*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_remove_request (struct request*) ; 
 int /*<<< orphan*/  elv_dispatch_sort (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_dispatch_insert(struct request_queue *q, struct request *rq)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	cfq_log_cfqq(cfqd, cfqq, "dispatch_insert");

	cfqq->next_rq = cfq_find_next_rq(cfqd, cfqq, rq);
	cfq_remove_request(rq);
	cfqq->dispatched++;
	(RQ_CFQG(rq))->dispatched++;
	elv_dispatch_sort(q, rq);

	cfqd->rq_in_flight[cfq_cfqq_sync(cfqq)]++;
	cfqq->nr_sectors += blk_rq_sectors(rq);
	cfq_blkiocg_update_dispatch_stats(&cfqq->cfqg->blkg, blk_rq_bytes(rq),
					rq_data_dir(rq), rq_is_sync(rq));
}