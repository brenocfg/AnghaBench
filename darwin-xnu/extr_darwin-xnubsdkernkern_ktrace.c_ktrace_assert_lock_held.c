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
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  ktrace_mtx ; 
 int /*<<< orphan*/  ktrace_single_threaded ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ktrace_assert_lock_held(void)
{
	if (!ktrace_single_threaded) {
		lck_mtx_assert(ktrace_mtx, LCK_MTX_ASSERT_OWNED);
	}
}