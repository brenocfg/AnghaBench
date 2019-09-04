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
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_geometry_lock ; 
 int /*<<< orphan*/  sysctl_lock_group ; 
 int /*<<< orphan*/  sysctl_register_set (char*) ; 
 int /*<<< orphan*/  sysctl_unlocked_node_lock ; 

void
sysctl_early_init(void)
{
	/*
	 * Initialize the geometry lock for reading/modifying the
	 * sysctl tree. This is done here because IOKit registers
	 * some sysctl's before bsd_init() would otherwise perform
	 * subsystem initialization.
	 */

	sysctl_lock_group  = lck_grp_alloc_init("sysctl", NULL);
	sysctl_geometry_lock = lck_rw_alloc_init(sysctl_lock_group, NULL);
	sysctl_unlocked_node_lock = lck_mtx_alloc_init(sysctl_lock_group, NULL);

	sysctl_register_set("__sysctl_set");
}