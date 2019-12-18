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
 int /*<<< orphan*/  acquire ; 
 int /*<<< orphan*/  init_test_mtx_stats () ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_atomic_cmpxchg (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_inc (int*,int /*<<< orphan*/ ) ; 
 int os_atomic_load (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  test_mtx ; 
 int /*<<< orphan*/  test_mtx_attr ; 
 int /*<<< orphan*/  test_mtx_grp ; 
 int /*<<< orphan*/  test_mtx_grp_attr ; 

void
lck_mtx_test_init(void)
{
	static int first = 0;

	/*
	 * This should be substituted with a version
	 * of dispatch_once for kernel (rdar:39537874)
	 */
	if (os_atomic_load(&first, acquire) >= 2)
		return;

	if (os_atomic_cmpxchg(&first, 0, 1, relaxed)){
		lck_grp_attr_setdefault(&test_mtx_grp_attr);
		lck_grp_init(&test_mtx_grp, "testlck_mtx", &test_mtx_grp_attr);
		lck_attr_setdefault(&test_mtx_attr);
		lck_mtx_init(&test_mtx, &test_mtx_grp, &test_mtx_attr);

		init_test_mtx_stats();

		os_atomic_inc(&first, release);
	}

	while(os_atomic_load(&first, acquire) < 2);
}