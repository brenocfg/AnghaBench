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
typedef  scalar_t__ lck_rw_type_t ;
typedef  int /*<<< orphan*/  lck_rw_t ;

/* Variables and functions */
 scalar_t__ LCK_RW_TYPE_EXCLUSIVE ; 
 scalar_t__ LCK_RW_TYPE_SHARED ; 
 int /*<<< orphan*/  lck_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

void
lck_rw_unlock(
	lck_rw_t	*lck,
	lck_rw_type_t	lck_rw_type)
{
	if (lck_rw_type == LCK_RW_TYPE_SHARED)
		lck_rw_unlock_shared(lck);
	else if (lck_rw_type == LCK_RW_TYPE_EXCLUSIVE)
		lck_rw_unlock_exclusive(lck);
	else
		panic("lck_rw_unlock(): Invalid RW lock type: %d\n", lck_rw_type);
}