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
struct throtl_grp {int /*<<< orphan*/  limits_changed; } ;
struct throtl_data {int /*<<< orphan*/  limits_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  throtl_schedule_delayed_work (struct throtl_data*,int /*<<< orphan*/ ) ; 
 int xchg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void throtl_update_blkio_group_common(struct throtl_data *td,
				struct throtl_grp *tg)
{
	int ret;

	ret = xchg(&tg->limits_changed, true);
	ret = xchg(&td->limits_changed, true);
	/* Schedule a work now to process the limit change */
	throtl_schedule_delayed_work(td, 0);
}