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

/* Variables and functions */
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shared_region_pager_lck_attr ; 
 int /*<<< orphan*/  shared_region_pager_lck_grp ; 
 int /*<<< orphan*/  shared_region_pager_lck_grp_attr ; 
 int /*<<< orphan*/  shared_region_pager_lock ; 
 int /*<<< orphan*/  shared_region_pager_queue ; 

void
shared_region_pager_bootstrap(void)
{
	lck_grp_attr_setdefault(&shared_region_pager_lck_grp_attr);
	lck_grp_init(&shared_region_pager_lck_grp, "shared_region", &shared_region_pager_lck_grp_attr);
	lck_attr_setdefault(&shared_region_pager_lck_attr);
	lck_mtx_init(&shared_region_pager_lock, &shared_region_pager_lck_grp, &shared_region_pager_lck_attr);
	queue_init(&shared_region_pager_queue);
}