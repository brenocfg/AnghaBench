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
struct request {int dummy; } ;
struct cfq_queue {TYPE_2__* cfqd; int /*<<< orphan*/ * queued; int /*<<< orphan*/  sort_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  blkg; } ;
struct TYPE_5__ {TYPE_1__* serving_group; } ;
struct TYPE_4__ {int /*<<< orphan*/  blkg; } ;

/* Variables and functions */
 TYPE_3__* RQ_CFQG (struct request*) ; 
 int /*<<< orphan*/  cfq_add_rq_rb (struct request*) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_io_add_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_io_remove_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  elv_rb_del (int /*<<< orphan*/ *,struct request*) ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 size_t rq_is_sync (struct request*) ; 

__attribute__((used)) static void cfq_reposition_rq_rb(struct cfq_queue *cfqq, struct request *rq)
{
	elv_rb_del(&cfqq->sort_list, rq);
	cfqq->queued[rq_is_sync(rq)]--;
	cfq_blkiocg_update_io_remove_stats(&(RQ_CFQG(rq))->blkg,
					rq_data_dir(rq), rq_is_sync(rq));
	cfq_add_rq_rb(rq);
	cfq_blkiocg_update_io_add_stats(&(RQ_CFQG(rq))->blkg,
			&cfqq->cfqd->serving_group->blkg, rq_data_dir(rq),
			rq_is_sync(rq));
}