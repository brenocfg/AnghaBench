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
struct as_data {int antic_status; int /*<<< orphan*/  antic_work; int /*<<< orphan*/  q; int /*<<< orphan*/  antic_timer; } ;

/* Variables and functions */
 int ANTIC_FINISHED ; 
 int ANTIC_WAIT_NEXT ; 
 int ANTIC_WAIT_REQ ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void as_antic_stop(struct as_data *ad)
{
	int status = ad->antic_status;

	if (status == ANTIC_WAIT_REQ || status == ANTIC_WAIT_NEXT) {
		if (status == ANTIC_WAIT_NEXT)
			del_timer(&ad->antic_timer);
		ad->antic_status = ANTIC_FINISHED;
		/* see as_work_handler */
		kblockd_schedule_work(ad->q, &ad->antic_work);
	}
}