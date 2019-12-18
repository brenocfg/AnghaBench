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
 int /*<<< orphan*/  kpc_config_lckgrp ; 
 int /*<<< orphan*/  kpc_config_lckgrp_attr ; 
 int /*<<< orphan*/  kpc_config_lock ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kpc_common_init(void)
{
	kpc_config_lckgrp_attr = lck_grp_attr_alloc_init();
	kpc_config_lckgrp = lck_grp_alloc_init("kpc", kpc_config_lckgrp_attr);
	lck_mtx_init(&kpc_config_lock, kpc_config_lckgrp, LCK_ATTR_NULL);
}