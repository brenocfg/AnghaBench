#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct request {int dummy; } ;
struct as_data {scalar_t__ antic_status; int /*<<< orphan*/ * next_rq; } ;

/* Variables and functions */
 scalar_t__ ANTIC_WAIT_NEXT ; 
 scalar_t__ ANTIC_WAIT_REQ ; 
 int /*<<< orphan*/  as_antic_stop (struct as_data*) ; 
 scalar_t__ as_can_break_anticipation (struct as_data*,struct request*) ; 
 int /*<<< orphan*/  as_choose_req (struct as_data*,struct request*,int /*<<< orphan*/ ) ; 
 int rq_is_sync (struct request*) ; 

__attribute__((used)) static void as_update_rq(struct as_data *ad, struct request *rq)
{
	const int data_dir = rq_is_sync(rq);

	/* keep the next_rq cache up to date */
	ad->next_rq[data_dir] = as_choose_req(ad, rq, ad->next_rq[data_dir]);

	/*
	 * have we been anticipating this request?
	 * or does it come from the same process as the one we are anticipating
	 * for?
	 */
	if (ad->antic_status == ANTIC_WAIT_REQ
			|| ad->antic_status == ANTIC_WAIT_NEXT) {
		if (as_can_break_anticipation(ad, rq))
			as_antic_stop(ad);
	}
}