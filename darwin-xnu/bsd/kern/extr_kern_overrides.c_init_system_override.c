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
 scalar_t__ cpu_throttle_assert_cnt ; 
 scalar_t__ fast_jetsam_assert_cnt ; 
 scalar_t__ io_throttle_assert_cnt ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sys_override_enabled ; 
 int /*<<< orphan*/  sys_override_lock ; 
 int /*<<< orphan*/  sys_override_mtx_attr ; 
 int /*<<< orphan*/  sys_override_mtx_grp ; 
 int /*<<< orphan*/  sys_override_mtx_grp_attr ; 

void
init_system_override()
{
	sys_override_mtx_grp_attr = lck_grp_attr_alloc_init();
	sys_override_mtx_grp = lck_grp_alloc_init("system_override", sys_override_mtx_grp_attr);
	sys_override_mtx_attr = lck_attr_alloc_init();
	lck_mtx_init(&sys_override_lock, sys_override_mtx_grp, sys_override_mtx_attr);
	io_throttle_assert_cnt = cpu_throttle_assert_cnt = fast_jetsam_assert_cnt = 0;
	sys_override_enabled = 1;
}