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
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  kpc_arch_init () ; 
 int /*<<< orphan*/  kpc_common_init () ; 
 int kpc_initted ; 
 int /*<<< orphan*/  kpc_thread_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_lckgrp ; 
 int /*<<< orphan*/  sysctl_lckgrp_attr ; 
 int /*<<< orphan*/  sysctl_lock ; 

void
kpc_init(void)
{
	sysctl_lckgrp_attr = lck_grp_attr_alloc_init();
	sysctl_lckgrp = lck_grp_alloc_init("kpc", sysctl_lckgrp_attr);
	lck_mtx_init(&sysctl_lock, sysctl_lckgrp, LCK_ATTR_NULL);

	kpc_arch_init();
	kpc_common_init();
	kpc_thread_init();

	kpc_initted = 1;
}