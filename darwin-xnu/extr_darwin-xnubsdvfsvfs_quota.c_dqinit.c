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
 void* lck_attr_alloc_init () ; 
 void* lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (void*,void*) ; 
 void* qf_lck_attr ; 
 void* qf_lck_grp ; 
 int /*<<< orphan*/  qf_lck_grp_attr ; 
 void* quota_list_lck_attr ; 
 void* quota_list_lck_grp ; 
 int /*<<< orphan*/  quota_list_lck_grp_attr ; 
 int /*<<< orphan*/  quota_list_mtx_lock ; 

void
dqinit(void)
{
	/*
	 * Allocate quota list lock group attribute and group
	 */
	quota_list_lck_grp_attr= lck_grp_attr_alloc_init();
	quota_list_lck_grp = lck_grp_alloc_init("quota list",  quota_list_lck_grp_attr);
	
	/*
	 * Allocate qouta list lock attribute
	 */
	quota_list_lck_attr = lck_attr_alloc_init();

	/*
	 * Allocate quota list lock
	 */
	quota_list_mtx_lock = lck_mtx_alloc_init(quota_list_lck_grp, quota_list_lck_attr);


	/*
	 * allocate quota file lock group attribute and group
	 */
	qf_lck_grp_attr= lck_grp_attr_alloc_init();
	qf_lck_grp = lck_grp_alloc_init("quota file", qf_lck_grp_attr);

	/*
	 * Allocate quota file lock attribute
	 */
	qf_lck_attr = lck_attr_alloc_init();
}