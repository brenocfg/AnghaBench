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
struct throtl_rb_root {scalar_t__ min_disptime; int /*<<< orphan*/  count; } ;
struct throtl_data {struct throtl_rb_root tg_service_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  throtl_schedule_delayed_work (struct throtl_data*,scalar_t__) ; 
 scalar_t__ time_before_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  total_nr_queued (struct throtl_data*) ; 
 int /*<<< orphan*/  update_min_dispatch_time (struct throtl_rb_root*) ; 

__attribute__((used)) static void throtl_schedule_next_dispatch(struct throtl_data *td)
{
	struct throtl_rb_root *st = &td->tg_service_tree;

	/*
	 * If there are more bios pending, schedule more work.
	 */
	if (!total_nr_queued(td))
		return;

	BUG_ON(!st->count);

	update_min_dispatch_time(st);

	if (time_before_eq(st->min_disptime, jiffies))
		throtl_schedule_delayed_work(td, 0);
	else
		throtl_schedule_delayed_work(td, (st->min_disptime - jiffies));
}