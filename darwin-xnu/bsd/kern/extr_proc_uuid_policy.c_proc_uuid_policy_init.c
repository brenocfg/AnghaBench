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
 int /*<<< orphan*/  M_PROC_UUID_POLICY ; 
 int /*<<< orphan*/  PROC_UUID_POLICY_HASH_SIZE ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_uuid_policy_count ; 
 int /*<<< orphan*/  proc_uuid_policy_hash_mask ; 
 int /*<<< orphan*/  proc_uuid_policy_hashtbl ; 
 int /*<<< orphan*/  proc_uuid_policy_subsys_lck_attr ; 
 int /*<<< orphan*/  proc_uuid_policy_subsys_lck_grp ; 
 int /*<<< orphan*/  proc_uuid_policy_subsys_lck_grp_attr ; 
 int /*<<< orphan*/  proc_uuid_policy_subsys_mutex ; 
 int proc_uuid_policy_table_gencount ; 

void
proc_uuid_policy_init(void)
{
	proc_uuid_policy_subsys_lck_grp_attr = lck_grp_attr_alloc_init();
	proc_uuid_policy_subsys_lck_grp = lck_grp_alloc_init("proc_uuid_policy_subsys_lock", proc_uuid_policy_subsys_lck_grp_attr);
	proc_uuid_policy_subsys_lck_attr = lck_attr_alloc_init();
	lck_mtx_init(&proc_uuid_policy_subsys_mutex, proc_uuid_policy_subsys_lck_grp, proc_uuid_policy_subsys_lck_attr);

	proc_uuid_policy_hashtbl = hashinit(PROC_UUID_POLICY_HASH_SIZE, M_PROC_UUID_POLICY, &proc_uuid_policy_hash_mask);
	proc_uuid_policy_table_gencount = 1;
	proc_uuid_policy_count = 0;
}