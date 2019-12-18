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
typedef  int /*<<< orphan*/  lck_rw_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_HELD ; 

__attribute__((used)) static void
cfil_rw_lock_assert_held(lck_rw_t *lck, int exclusive)
{
#if !MACH_ASSERT
#pragma unused(lck, exclusive)
#endif
	LCK_RW_ASSERT(lck,
	    exclusive ? LCK_RW_ASSERT_EXCLUSIVE : LCK_RW_ASSERT_HELD);
}