#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int cmd_flags; int /*<<< orphan*/  queuelist; } ;
struct cfq_queue {int /*<<< orphan*/  meta_pending; TYPE_1__* cfqd; struct request* next_rq; } ;
struct TYPE_4__ {int /*<<< orphan*/  blkg; } ;
struct TYPE_3__ {int /*<<< orphan*/  rq_queued; } ;

/* Variables and functions */
 int REQ_META ; 
 TYPE_2__* RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_io_remove_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_del_rq_rb (struct request*) ; 
 struct request* cfq_find_next_rq (TYPE_1__*,struct cfq_queue*,struct request*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_remove_request(struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	if (cfqq->next_rq == rq)
		cfqq->next_rq = cfq_find_next_rq(cfqq->cfqd, cfqq, rq);

	list_del_init(&rq->queuelist);
	cfq_del_rq_rb(rq);

	cfqq->cfqd->rq_queued--;
	cfq_blkiocg_update_io_remove_stats(&(RQ_CFQG(rq))->blkg,
					rq_data_dir(rq), rq_is_sync(rq));
	if (rq->cmd_flags & REQ_META) {
		WARN_ON(!cfqq->meta_pending);
		cfqq->meta_pending--;
	}
}