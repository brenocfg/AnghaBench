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
 int /*<<< orphan*/  fourk_pager_lck_attr ; 
 int /*<<< orphan*/  fourk_pager_lck_grp ; 
 int /*<<< orphan*/  fourk_pager_lck_grp_attr ; 
 int /*<<< orphan*/  fourk_pager_lock ; 
 int /*<<< orphan*/  fourk_pager_queue ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 

void
fourk_pager_bootstrap(void)
{
	lck_grp_attr_setdefault(&fourk_pager_lck_grp_attr);
	lck_grp_init(&fourk_pager_lck_grp, "4K-pager", &fourk_pager_lck_grp_attr);
	lck_attr_setdefault(&fourk_pager_lck_attr);
	lck_mtx_init(&fourk_pager_lock, &fourk_pager_lck_grp, &fourk_pager_lck_attr);
	queue_init(&fourk_pager_queue);
}