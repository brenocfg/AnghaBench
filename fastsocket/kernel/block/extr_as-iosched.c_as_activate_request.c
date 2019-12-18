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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct TYPE_4__ {TYPE_1__* aic; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_dispatched; } ;

/* Variables and functions */
 scalar_t__ AS_RQ_DISPATCHED ; 
 int /*<<< orphan*/  AS_RQ_REMOVED ; 
 TYPE_2__* RQ_IOC (struct request*) ; 
 int /*<<< orphan*/  RQ_SET_STATE (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ RQ_STATE (struct request*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void as_activate_request(struct request_queue *q, struct request *rq)
{
	WARN_ON(RQ_STATE(rq) != AS_RQ_DISPATCHED);
	RQ_SET_STATE(rq, AS_RQ_REMOVED);
	if (RQ_IOC(rq) && RQ_IOC(rq)->aic)
		atomic_dec(&RQ_IOC(rq)->aic->nr_dispatched);
}