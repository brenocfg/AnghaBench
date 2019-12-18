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
struct delayed_work {int dummy; } ;
struct throtl_data {scalar_t__ limits_changed; struct delayed_work throtl_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cancel_delayed_work (struct delayed_work*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kthrotld_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,struct delayed_work*,unsigned long) ; 
 int /*<<< orphan*/  throtl_log (struct throtl_data*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ total_nr_queued (struct throtl_data*) ; 

__attribute__((used)) static void
throtl_schedule_delayed_work(struct throtl_data *td, unsigned long delay)
{

	struct delayed_work *dwork = &td->throtl_work;

	/* schedule work if limits changed even if no bio is queued */
	if (total_nr_queued(td) > 0 || td->limits_changed) {
		/*
		 * We might have a work scheduled to be executed in future.
		 * Cancel that and schedule a new one.
		 */
		__cancel_delayed_work(dwork);
		queue_delayed_work(kthrotld_workqueue, dwork, delay);
		throtl_log(td, "schedule work. delay=%lu jiffies=%lu",
				delay, jiffies);
	}
}