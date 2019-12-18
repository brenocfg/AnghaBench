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
struct cfq_data {scalar_t__ last_position; int /*<<< orphan*/  rq_in_driver; } ;
struct TYPE_2__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_CFQQ (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_activate_request(struct request_queue *q, struct request *rq)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;

	cfqd->rq_in_driver++;
	cfq_log_cfqq(cfqd, RQ_CFQQ(rq), "activate rq, drv=%d",
						cfqd->rq_in_driver);

	cfqd->last_position = blk_rq_pos(rq) + blk_rq_sectors(rq);
}