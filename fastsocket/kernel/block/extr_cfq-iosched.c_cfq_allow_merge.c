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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct cfq_queue {int dummy; } ;
struct cfq_io_context {int dummy; } ;
struct cfq_data {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  io_context; } ;
struct TYPE_3__ {struct cfq_data* elevator_data; } ;

/* Variables and functions */
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 scalar_t__ cfq_bio_sync (struct bio*) ; 
 struct cfq_io_context* cfq_cic_lookup (struct cfq_data*,int /*<<< orphan*/ ) ; 
 struct cfq_queue* cic_to_cfqq (struct cfq_io_context*,scalar_t__) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  rq_is_sync (struct request*) ; 

__attribute__((used)) static int cfq_allow_merge(struct request_queue *q, struct request *rq,
			   struct bio *bio)
{
	struct cfq_data *cfqd = q->elevator->elevator_data;
	struct cfq_io_context *cic;
	struct cfq_queue *cfqq;

	/*
	 * Disallow merge of a sync bio into an async request.
	 */
	if (cfq_bio_sync(bio) && !rq_is_sync(rq))
		return false;

	/*
	 * Lookup the cfqq that this bio will be queued with. Allow
	 * merge only if rq is queued there.
	 */
	cic = cfq_cic_lookup(cfqd, current->io_context);
	if (!cic)
		return false;

	cfqq = cic_to_cfqq(cic, cfq_bio_sync(bio));
	return cfqq == RQ_CFQQ(rq);
}