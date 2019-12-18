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
struct workqueue {int dummy; } ;
struct workq_threadreq_s {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  abstime; int /*<<< orphan*/  usecs; } ;
struct TYPE_5__ {int /*<<< orphan*/  abstime; int /*<<< orphan*/  usecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  abstime; int /*<<< orphan*/  usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  workq_lck_attr ; 
 int /*<<< orphan*/  workq_lck_grp ; 
 int /*<<< orphan*/  workq_lck_grp_attr ; 
 void* workq_zone_threadreq ; 
 void* workq_zone_workqueue ; 
 TYPE_3__ wq_max_timer_interval ; 
 TYPE_2__ wq_reduce_pool_window ; 
 TYPE_1__ wq_stalled_window ; 
 void* zinit (int,int,int,char*) ; 

void
workq_init(void)
{
	workq_lck_grp_attr = lck_grp_attr_alloc_init();
	workq_lck_attr = lck_attr_alloc_init();
	workq_lck_grp = lck_grp_alloc_init("workq", workq_lck_grp_attr);

	workq_zone_workqueue = zinit(sizeof(struct workqueue),
			1024 * sizeof(struct workqueue), 8192, "workq.wq");
	workq_zone_threadreq = zinit(sizeof(struct workq_threadreq_s),
			1024 * sizeof(struct workq_threadreq_s), 8192, "workq.threadreq");

	clock_interval_to_absolutetime_interval(wq_stalled_window.usecs,
			NSEC_PER_USEC, &wq_stalled_window.abstime);
	clock_interval_to_absolutetime_interval(wq_reduce_pool_window.usecs,
			NSEC_PER_USEC, &wq_reduce_pool_window.abstime);
	clock_interval_to_absolutetime_interval(wq_max_timer_interval.usecs,
			NSEC_PER_USEC, &wq_max_timer_interval.abstime);
}