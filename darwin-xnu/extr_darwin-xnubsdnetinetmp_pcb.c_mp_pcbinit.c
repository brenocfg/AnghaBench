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
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_lock ; 
 int /*<<< orphan*/  mp_lock_attr ; 
 int /*<<< orphan*/  mp_lock_grp ; 
 int /*<<< orphan*/  mp_lock_grp_attr ; 
 int /*<<< orphan*/  mp_timeout_lock ; 

void
mp_pcbinit(void)
{
	static int mp_initialized = 0;

	VERIFY(!mp_initialized);
	mp_initialized = 1;

	mp_lock_grp_attr = lck_grp_attr_alloc_init();
	mp_lock_grp = lck_grp_alloc_init("multipath", mp_lock_grp_attr);
	mp_lock_attr = lck_attr_alloc_init();
	lck_mtx_init(&mp_lock, mp_lock_grp, mp_lock_attr);
	lck_mtx_init(&mp_timeout_lock, mp_lock_grp, mp_lock_attr);
}